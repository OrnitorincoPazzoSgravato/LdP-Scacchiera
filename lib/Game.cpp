/**
 * @file Game.cpp
 * @author Riccardo Zuech
 * @brief 
 * @version 0.1
 * @date 2022-01-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "../include/Game.h";

#include <random>

#include "../include/Bot.h";
#include "../include/Utilities.h";


namespace gameplay {
	
    // constructors declaration
    Game::Game() : n_moves{0}, en_passante_coord{nullptr}, board{chessgame::Chessboard()} {
        std::array<chessgame::PieceColor&, 2> a_colors = this->getRandColors();
        this->p1 = std::make_unique<chessgame::Player>(chessgame::Player(a_colors[0]));
        this->p2 = std::make_unique<chessgame::Player>(chessgame::Bot(a_colors[1]));
    }

    Game::Game(bool is_bot_match) : Game() {
        if(is_bot_match)
            this->p1.reset(new chessgame::Bot(p1.get()->pieceColor));
    }

    // destructor declaration
    Game::~Game() {
        if(this->log_file.is_open()) this->log_file.close();
    }

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

    char Game::promotion(const chessgame::Coordinates& coord) {
        // piece to check for promotion
        chessgame::Piece *p = this->board.get_piece(coord);
        // a white paw on the top row or a black paw on the bottom row
        if((p->getSymbol() == 'p' && coord.x == 0) || (p->getSymbol() == 'P' && coord.x == 7)) {

			p = nullptr; // good practice. Now p isn't needed anymore

			// "asks" the player for the promotion target and proceeds to update the board
            chessgame::Piece *new_p = (this->current_turn ? this->p1 : this->p2)->getPromotionTarget();
			this->board.set_piece(coord, new_p);
			
			char new_symbol = new_p->getSymbol();
			p = nullptr;
			return new_symbol; // successful promotion
        }
		p = nullptr;
		return 0; // promotion not required
    }

	void Game::updateFirstMove(chessgame::Piece* p) {
		if(p == nullptr) return;
		// symbol of the piece to update
		const char kPiece_symbol = p->getSymbol();
		if(kPiece_symbol == 'r' || kPiece_symbol == 'R') dynamic_cast<chessgame::Re*>(p)->has_already_moved = true;
		else if(kPiece_symbol == 'p' || kPiece_symbol == 'P') dynamic_cast<chessgame::Pedone*>(p)->has_already_moved = true;
		else if(kPiece_symbol == 't' || kPiece_symbol == 'T') dynamic_cast<chessgame::Torre*>(p)->has_already_moved = true;
	}

	std::string Game::legalTurnCleanUp(std::array<chessgame::Coordinates, 2> move, chessgame::Piece& p) {
		return this->legalTurnCleanUp(move, p, nullptr);
	}

	std::string Game::legalTurnCleanUp(std::array<chessgame::Coordinates, 2> move, chessgame::Piece& p_coord1, chessgame::Piece* p_coord2) {
		// the log move for the current move
		std::string log_move = move[0].symbol + ' ' + move[1].symbol;

		// symbol of the piece to move
		const char kPiece_symbol = p_coord1.getSymbol();
		
		// here the piece is finally moved
		this->board.set_piece(move[1], &p_coord1);
		this->board.set_piece(move[0], p_coord2);

		// updates "has_already_moved" attribute for paws, kings and towers
		this->updateFirstMove(&p_coord1);
		this->updateFirstMove(p_coord2);

		char promotion_input = this->promotion(move[1]); // calls the function that manage the special rule "promotion"
		if(promotion_input != 0) // successful promotion, as per documentation
			log_move += ("\n" + promotion_input);

		return log_move;
	}

    // public methods declaration
    void Game::play() {
        this->log_file.open("game_log.txt"); // open the log file

        do {
            // holds the string representing the move to be logged
            std::string log_move;

            bool invalid_move = true;
            do {
                // player's move for its turn
                std::array<chessgame::Coordinates,2>& move = this->current_turn ? this->p1->think() : this->p2->think();

                // selected piece to move
                chessgame::Piece *p = this->board.get_piece(move[0]);

				// if we're trying to move a non-existing piece obviously it's an invalid move
				if(p != nullptr) {
					// symbol of the piece to move
					const char kPiece_symbol = p->getSymbol();

					// selected piece's default legal moves
					std::vector<chessgame::Coordinates> legal_moves_vec = p->getMoves(this->board, move[1]);
					for(int i = 0; i < legal_moves_vec.size(); i++) {
						if(move[1] == legal_moves_vec[i]) invalid_move = false; // if the move has been found, then it must be valid
					}

					if(!invalid_move) log_move = this->legalTurnCleanUp(move, *p); // valid call as we are sure that p is not a nullptr

					// the block below checks for potential special rules moves if it's *not* a defaultly  allowed one
					if(invalid_move) {
						// special rule: en_passant
						bool p_is_paw = kPiece_symbol == 'p' || kPiece_symbol == 'P';
						// it's a paw trying to capture another pow that previously moved by two tiles
						if(this->en_passante_coord != nullptr && p_is_paw && move[1] == *(this->en_passante_coord)) {
							log_move = this->legalTurnCleanUp(move, *p);
						}
						// it's a paw that has already to move and should be moved by two tiles
						if(p_is_paw && !(dynamic_cast<chessgame::Pedone*>(p)->has_already_moved) && move[0].x == move[1].x && std::abs(move[0].y - move[1].y) == 2) {
							log_move = this->legalTurnCleanUp(move, *p);
							this->en_passante_coord = &move[1];
						}
						else this->en_passante_coord = nullptr; // used to reset at the next turn

						// destination's piece
               			chessgame::Piece *dest_p = this->board.get_piece(move[1]);

						// special rule: "arrocco"
						if(dest_p != nullptr && p->getColor() == dest_p->getColor()) { // not a nullptr and same color
							const char kDest_p_symbol = dest_p->getSymbol();
							bool p_Is_King = kPiece_symbol == 'r' || kPiece_symbol == 'R';
							bool p_Is_Tower = kPiece_symbol == 't' || kPiece_symbol == 'T';
							bool dest_Is_King = kDest_p_symbol == 'r' || kDest_p_symbol == 'R';
							bool dest_Is_Tower = kDest_p_symbol == 't' || kDest_p_symbol == 'r';

							bool king_in_tower = p_Is_King && dest_Is_Tower;
							bool tower_in_king = p_Is_Tower && dest_Is_King;

							if(king_in_tower || tower_in_king) {
								bool is_tower_first_move = dynamic_cast<chessgame::Torre*>(dest_p)->has_already_moved;
								bool is_king_first_move = dynamic_cast<chessgame::Re*>(dest_p)->has_already_moved;
								if(is_king_first_move && is_tower_first_move) {
									const int kY = move[0].y; // same row as they still have to make a move

									bool obstacles = false;
									int index = move[0].x < move[1].x ? move[0].x : move[1].x;
									int end_index = move[0].x < move[1].x ? move[1].x : move[0].x;
									for(; index <= end_index && !obstacles; index++) {
										if(this->board.get_piece(chessgame::Coordinates(kY, index)) != nullptr) obstacles == true;
									}

									// if there are no obstacles then the "arrocco" is legal
									if(!obstacles) log_move = this->legalTurnCleanUp(move, *p, dest_p);
								}
							}
						}
						
						dest_p = nullptr; // clears dest_p pointer after use
					}
					p = nullptr; // clears p pointer after use
				}

            } while(invalid_move); // this cycle keeps going until a valid move has been entered

            this->log_file << log_move << '\n'; // outputs move to the log file

			std::cout << this->board.snapshot() << '\n';

            this->n_moves++; // increse number of moves

            this->current_turn = !this->current_turn; // alternates turns
        } while(!this->isGameOver());

        this->log_file.close(); // closes the log file
    }
}

