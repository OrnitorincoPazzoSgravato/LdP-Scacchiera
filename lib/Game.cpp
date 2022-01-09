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
        std::array<chessgame::PieceColor, 2> a_colors = this->getRandColors();
        this->p1 = chessgame::Player(a_colors[0]);
        this->p2 = chessgame::Bot(a_colors[1], this->board);
    }

    Game::Game(bool is_bot_match) : Game() {
        if(is_bot_match)
            this->p1 = chessgame::Bot(this->p1.getColor(), this->board);
    }

    // destructor declaration
    Game::~Game() {
        if(this->log_file.is_open()) this->log_file.close();
    }

    // private methods declaration
    std::array<chessgame::PieceColor, 2>& Game::getRandColors() {
        std::array<chessgame::PieceColor, 2> c_array; // declaration of the returned array

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
            chessgame::Piece *new_p = (this->current_turn ? this->p1 : this->p2).getPromotionTarget();
			this->board.set_piece(coord, new_p);
			
			char new_symbol = new_p->getSymbol();
			p = nullptr;
			return new_symbol; // successful promotion
        }
		p = nullptr;
		return 0; // promotion not required
    }

	void Game::updateFirstMove(const chessgame::Coordinates& coord) {
		chessgame::Piece* p = this->board.get_piece(coord);
		if(p == nullptr) return;
		// symbol of the piece to update
		const char kPiece_symbol = p->getSymbol();
		if(kPiece_symbol == 'r' || kPiece_symbol == 'R') dynamic_cast<chessgame::Re*>(p)->has_already_moved = true;
		else if(kPiece_symbol == 'p' || kPiece_symbol == 'P') dynamic_cast<chessgame::Pedone*>(p)->has_already_moved = true;
		else if(kPiece_symbol == 't' || kPiece_symbol == 'T') dynamic_cast<chessgame::Torre*>(p)->has_already_moved = true;
	}

	std::string Game::legalTurnCleanUp(const std::array<chessgame::Coordinates, 2>& move, bool is_swap = false) {
		// the log move for the current move
		std::string log_move = move[0].symbol + ' ' + move[1].symbol;
		
		if(!is_swap && this->board.get_piece(move[1]) != nullptr) { // this is a capture movement
			this->board.set_piece(move[1], nullptr);
		}
		// here the piece is finally moved
		this->board.swap_positions(move[0], move[1]);

		// updates "has_already_moved" attribute for paws, kings and towers
		this->updateFirstMove(move[1]);
		this->updateFirstMove(move[0]);

		char promotion_input = this->promotion(move[1]); // calls the function that manage the special rule "promotion"
		if(promotion_input != 0) // successful promotion, as per documentation
			log_move += ("\n" + promotion_input);

		return log_move;
	}

	std::array<chessgame::Coordinates,2>& Game::askMove() {
		return this->current_turn ? this->p1.think() : this->p2.think();
	}

	bool Game::isKingInCheck() {
		chessgame::Coordinates king_coord = this->current_turn ? this->p1_king_coord : this->p2_king_coord;
		for(int y = 0; y < 8; y++) {
			for(int x = 0; x < 8; x++) {
				chessgame::Coordinates piece_coord = chessgame::Coordinates(x, y);
				chessgame::Piece* p = this->board.get_piece(piece_coord);
				if(p != nullptr) {
					std::vector<chessgame::Coordinates> moves_vec = p->getMoves(this->board, piece_coord);
					for(auto it = moves_vec.begin(); it == moves_vec.end(); it++) {
						if(*it == king_coord) return true;
					}
				}
			}
		}
		return false;
	}

	bool Game::isPawTwoTilesMovement(std::array<chessgame::Coordinates, 2>& move) {
		chessgame::Piece* p = this->board.get_piece(move[0]);
		if(p == nullptr) return false;
		bool p_is_paw = p->getSymbol() == 'p' || p->getSymbol() == 'P';
		if(p_is_paw && !(dynamic_cast<chessgame::Pedone*>(p)->has_already_moved) &&
			move[0].x == move[1].x && std::abs(move[0].y - move[1].y) == 2 &&
			this->board.get_piece(move[1]) == nullptr) {
				p = nullptr;
				this->en_passante_coord = &move[1];
				return true;
		}
		p = nullptr;
		return false;
	}

	bool Game::isEnPassant(char piece_symbol, const chessgame::Coordinates& to) {
		bool p_is_paw = piece_symbol == 'p' || piece_symbol == 'P';
		// en_passant is appliable
		if(this->en_passante_coord != nullptr) {
			this->en_passante_coord = nullptr; // used to reset the flag
			// it's a paw trying to capture another paw that previously moved by two tiles
			if(p_is_paw && to == *(this->en_passante_coord)) return true;
		}
		return false;
	}

	bool Game::isMoveArrocco(const std::array<chessgame::Coordinates, 2>& move) {
		chessgame::Piece* p = this->board.get_piece(move[0]);
		if(p == nullptr) return false;

		chessgame::Piece* dest_p = this->board.get_piece(move[1]);
		
		char piece_symbol = p->getSymbol();

		if(dest_p != nullptr && p->getColor() == dest_p->getColor()) { // not a nullptr and same color
			const char kDest_p_symbol = dest_p->getSymbol();
			bool p_Is_King = piece_symbol == 'r' || piece_symbol == 'R';
			bool p_Is_Tower = piece_symbol == 't' || piece_symbol == 'T';
			bool dest_Is_King = kDest_p_symbol == 'r' || kDest_p_symbol == 'R';
			bool dest_Is_Tower = kDest_p_symbol == 't' || kDest_p_symbol == 'r';

			bool king_in_tower = p_Is_King && dest_Is_Tower;
			bool tower_in_king = p_Is_Tower && dest_Is_King;

			if(king_in_tower || tower_in_king) {
				// the conditional operator is used to differentiate between king or tower istance as the object pointed by p (and so dest_p)
				bool is_tower_first_move = dynamic_cast<chessgame::Torre*>(king_in_tower ? dest_p : p)->has_already_moved;
				bool is_king_first_move = dynamic_cast<chessgame::Re*>(king_in_tower ? p : dest_p)->has_already_moved;
				if(is_king_first_move && is_tower_first_move) {
					const int kY = move[0].y; // same row as they still have to make a move

					bool obstacles = false;
					int index = move[0].x < move[1].x ? move[0].x : move[1].x;
					int end_index = move[0].x < move[1].x ? move[1].x : move[0].x;
					for(; index <= end_index && !obstacles; index++) {
						if(this->board.get_piece(chessgame::Coordinates(kY, index)) != nullptr) obstacles == true;
					}

					// if there are no obstacles then the special rule is legal
					return !obstacles;
				}
			}
		}
		p = nullptr;
		dest_p = nullptr; // clears dest_p pointer after use

		return false;
	}

	bool Game::canDefaultlyMove(chessgame::Piece& p, const chessgame::Coordinates& to) {
		// selected piece's default legal moves
		std::vector<chessgame::Coordinates> legal_moves_vec = p.getMoves(this->board, to);
		for(int i = 0; i < legal_moves_vec.size(); i++) {
			if(legal_moves_vec[i] == to) return true; // if the move has been found, then it must be valid
		}
		return false;
	}
	
	// the idea is to keep asking for moves until one resolves the check:
	// 1) the king can move away
	// 2) an obstacle can be created
	// 3) the piece checking the king can be captured
	// Solution: try moving, check if it resolves the check and then apply the proper cleanup
	bool Game::manageCheckState(std::array<chessgame::Coordinates, 2>& move) {

		chessgame::Piece* p = this->board.get_piece(move[0]);
		if(p == nullptr) return false;

		/*
		possibili mosse:
		spostamento a casella vuota x
		arrocco x
		en passant x
		cattura x
		*/
		bool is_default = this->canDefaultlyMove(*p, move[1]);
		bool is_paw_movement = this->isPawTwoTilesMovement(move);
		bool is_arrocco = this->isMoveArrocco(move);

		bool is_capture = (is_default && this->board.get_piece(move[1]) != nullptr) || this->isEnPassant(p->getSymbol(), move[1]);
		chessgame::Piece* captured_p = nullptr;

		if(is_default || is_arrocco || is_paw_movement) {
			this->board.swap_positions(move[0], move[1]);
			if(is_capture && !is_arrocco) {
				this->board.set_piece(move[0], nullptr); // questo però elimina il pezzo
			}
		}

		return false;
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
                std::array<chessgame::Coordinates,2>& move = askMove();

				chessgame::Piece* p = this->board.get_piece(move[0]);
				
				// if we're trying to move a non-existing piece obviously it's an invalid move
				if(p != nullptr) {
					// symbol of the piece to move
					char piece_symbol = p->getSymbol();

					// block used to manage a possible king check
					if(this->isKingInCheck()) {

						invalid_move = manageCheckState(move);
						if(!invalid_move) log_move = move[0].symbol + ' ' + move[1].symbol;
						// TBD
					}
					else {
						// default rules or en passant or paw two tiles movement
						if(this->canDefaultlyMove(*p, move[1]) || this->isEnPassant(piece_symbol, move[1]) || isPawTwoTilesMovement(move)) {
							invalid_move = false;
							log_move = this->legalTurnCleanUp(move);
						}
						// special rule arrocco
						else if(this->isMoveArrocco(move)) {
							invalid_move = false;
							log_move = this->legalTurnCleanUp(move, true);
							if(piece_symbol == 't' || piece_symbol == 'T') {
								// updates the king position
								this->current_turn ? this->p1_king_coord = move[0] : this->p2_king_coord = move[0];
							}
						}
						
						// updates the player's king position if it has been moved
						if(!invalid_move && (piece_symbol == 'r' || piece_symbol == 'R')) {
							this->current_turn ? this->p1_king_coord = move[1] : this->p2_king_coord = move[1];
						}
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

