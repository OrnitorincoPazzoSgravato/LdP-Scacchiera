#include "../include/Game.h";
#include "../include/Player.h";
#include "../include/Bot.h";
#include "../include/Utilities.h";

#include <random>

// private methods declaration
std::array<chessgame::PieceColor&, 2> chessgame::Game::getRandColors() {
    std::array<chessgame::PieceColor&, 2> c_array; // declaration of the returned array

    double rand_num = std::rand();  // std library rand function to get a random number between 0 and 1
    // based on rand_num c_array is initialized with different values (just two possible outcomes, so an if-else is enough to cover them)
    if(rand_num < 0.5) c_array = {chessgame::PieceColor::BLACK, chessgame::PieceColor::WHITE};
    else c_array = {chessgame::PieceColor::WHITE, chessgame::PieceColor::BLACK};
    return c_array;
}

bool chessgame::Game::writeLog(const std::string& move) {
    this->log_file << move << '\n';
}

bool chessgame::Game::isGameOver() {
    // block used to check if a bot game has reached its max amount of moves (game ending condition)
    if(this->n_moves >= chessgame::Game::kBot_moves) {
        std::cout << "The full-bot game has reached its maximum amount of moves without ending {" << chessgame::Game::kBot_moves << "}. Please try again." << std::endl;
        return true;
    }
    // TBD
    return false; // default return value
}

// constructors declaration
chessgame::Game::Game() : n_moves{0} {
    std::array<chessgame::PieceColor&, 2> a_colors = this->getRandColors();
    this->p1 = std::make_unique<chessgame::Player>(new chessgame::Player(a_colors[0]));
    this->p2 = std::make_unique<chessgame::Player>(new chessgame::Bot(a_colors[1]));

    this->board = chessgame::Chessboard();
}

chessgame::Game::Game(bool is_bot_match) : Game() {
    if(is_bot_match)
        this->p1.reset(new chessgame::Bot(p1.get()->pc));
}

// destructor declaration
chessgame::Game::~Game() {
    if(this->log_file.is_open()) this->log_file.close();
}

// public methods declaration
void chessgame::Game::play() {
    this->log_file.open("game_log.txt"); // open the log file

    do {
        bool invalid_move = true;
        do {
            // player's move for its turn
            std::array<chessgame::Coordinates,2>& move = this->current_turn ? this->p1->think() : this->p2->think();

            // selected piece
            chessgame::Piece *p = this->board.get_piece(move[0]);

            // selected piece's default legal moves
            std::vector<chessgame::Coordinates> legal_moves_vec = p->getMoves(this->board, move[1]);
            for(int i = 0; i < legal_moves_vec.size(); i++) {
                if(move[1] == legal_moves_vec[i]) invalid_move = false; // if the move has been found, then it must be valid
            }

            // the block below checks for potential special rules moves (only if *not* a defaultly  allowed move)
            if(invalid_move) {
                // TBD
            }
        } while(invalid_move); // this cycle keeps going until a valid move has been entered

        this->n_moves++; // increse number of moves

        this->current_turn = !this->current_turn; // alternates turns
    } while(!this->isGameOver());

    this->log_file.close(); // closes the log file
}