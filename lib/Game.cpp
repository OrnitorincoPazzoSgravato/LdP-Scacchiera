#include "../include/Game.h";

#include <random>

#include "../include/Bot.h";
#include "../include/Utilities.h";


namespace gameplay {

    // private methods declaration
    std::array<chessgame::PieceColor&, 2> Game::getRandColors() {
        std::array<chessgame::PieceColor&, 2> c_array; // declaration of the returned array

        double rand_num = std::rand();  // std library rand function to get a random number between 0 and 1
        // based on rand_num c_array is initialized with different values (just two possible outcomes, so an if-else is enough to cover them)
        if(rand_num < 0.5) c_array = {chessgame::PieceColor::BLACK, chessgame::PieceColor::WHITE};
        else c_array = {chessgame::PieceColor::WHITE, chessgame::PieceColor::BLACK};
        return c_array;
    }

    bool Game::writeLog(const std::string& move) {
        this->log_file << move << '\n';
    }

    bool Game::isGameOver() {
        // block used to check if a bot game has reached its max amount of moves (game ending condition)
        if(this->n_moves >= Game::kBot_moves) {
            std::cout << "The full-bot game has reached its maximum amount of moves without ending {" << Game::kBot_moves << "}. Please try again." << std::endl;
            return true;
        }
        // TBD
        return false; // default return value
    }

    // constructors declaration
    Game::Game() : n_moves{0} {
        std::array<chessgame::PieceColor&, 2> a_colors = this->getRandColors();
        this->p1 = std::make_unique<chessgame::Player>(new chessgame::Player(a_colors[0]));
        this->p2 = std::make_unique<chessgame::Player>(new chessgame::Bot(a_colors[1]));

        this->board = chessgame::Chessboard();
    }

    Game::Game(bool is_bot_match) : Game() {
        if(is_bot_match)
            this->p1.reset(new chessgame::Bot(p1.get()->pc));
    }

    // destructor declaration
    Game::~Game() {
        if(this->log_file.is_open()) this->log_file.close();
    }

    // public methods declaration
    void Game::play() {
        this->log_file.open("game_log.txt"); // open the log file

        do {
            // selected piece to move
            chessgame::Piece *p;
            // will hold the string representing the player move
            std::string log_move;

            bool invalid_move = true;
            do {
                // player's move for its turn
                std::array<chessgame::Coordinates,2>& move = this->current_turn ? this->p1->think() : this->p2->think();

                // retrieves a pointer to the piece being moved
                p = this->board.get_piece(move[0]);

                // selected piece's default legal moves
                std::vector<chessgame::Coordinates> legal_moves_vec = p->getMoves(this->board, move[1]);
                for(int i = 0; i < legal_moves_vec.size(); i++) {
                    if(move[1] == legal_moves_vec[i]) invalid_move = false; // if the move has been found, then it must be valid
                }

                // the block below checks for potential special rules moves if it's *not* a defaultly  allowed one
                if(invalid_move) {
                    // TBD
                }

                // block used to call "clean-up functions": functions to be called only when a move is finally valid
                if(!invalid_move) {
                    log_move = move[0].symbol + ' ' + move[1].symbol;   // generates the log move for the current move

                    // PROMOZIONE TBD
                }

            } while(invalid_move); // this cycle keeps going until a valid move has been entered

            this->log_file << log_move << '\n'; // outputs move to the log file

            this->n_moves++; // increse number of moves

            this->current_turn = !this->current_turn; // alternates turns
        } while(!this->isGameOver());

        this->log_file.close(); // closes the log file
    }
}

