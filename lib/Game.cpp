/**
 * @file Game.cpp
 * @author Riccardo Zuech
 * @brief Definition of methods of Game
 * @version 0.1
 * @date 2022-01-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "../include/Game.h"

#include <random>
#include <time.h>

#include "../include/chessgame/Player.h"
#include "../include/chessgame/Human.h"
#include "../include/chessgame/Bot.h"
#include "../include/chessgame/Utilities.h"
#include "../include/chessgame/Chessboard.h"
#include "../include/chessgame/Piece.h"

namespace gameplay
{
    // namespace helper functions definition
    bool isArrocco(const std::array<chessgame::Coordinates, 2> &move, const chessgame::Chessboard &board)
    {
        chessgame::Piece *p = board.get_piece(move[0]);
        if (p == nullptr) // obviously an istance of arrocco needs a piece
            return false;

        char piece_symbol = p->getSymbol();

        // p must be a king
        bool p_Is_King = piece_symbol == chessgame::BLACK_KING || piece_symbol == chessgame::WHITE_KING;
        // p must move of two tiles horizontally
        bool two_columns_move = std::abs(move[0].x - move[1].x) == 2 && move[0].y == move[1].y;
        // p must also be a king already to move
        if(p_Is_King && !dynamic_cast<chessgame::Re *>(p)->has_already_moved && two_columns_move) {
            int x, x_end;
            chessgame::Piece* p_angle = nullptr;
            if(move[0].x == (move[1].x - 2)) { // short arrocco
                p_angle = move[0] == chessgame::Coordinates{"E8"} ? board.get_piece(chessgame::Coordinates{"H8"}) : board.get_piece(chessgame::Coordinates{"H1"});
                x = 5;
                x_end = 7;
            }
            else if(move[0].x == (move[1].x + 2)) { // long arrocco
                p_angle = move[0] == chessgame::Coordinates{"E1"} ? board.get_piece(chessgame::Coordinates{"A1"}) : board.get_piece(chessgame::Coordinates{"A8"});
                x = 1;
                x_end = 4;
            }
            // p angle must be a tower
            bool p_angle_is_tower = p_angle != nullptr && (p_angle->getSymbol() == chessgame::BLACK_TOWER || p_angle->getSymbol() == chessgame::WHITE_TOWER);
            // and also a tower that has already to move
            bool moved = !(p_angle_is_tower && !dynamic_cast<chessgame::Torre* >(p_angle)->has_already_moved);
            if(moved) return false;

            for(; x < x_end; x++) {
                if(board.get_piece(chessgame::Coordinates{x, move[0].y}) != nullptr) // there must be no obstacles between the tower and the king
                    return false;
            }
            return true;
        }
        return false;
    }
    
    // constructors definitions
    Game::Game() : n_moves{0}, en_passante_coord{nullptr}, stall_counter{0}, is_bot_game{false}
    {
        std::srand(time(NULL)); // seed to make random different at each run

        std::array<chessgame::PieceColor, 2> a_colors = this->getRandColors(); // retrieves random colors
        this->p1 = new chessgame::Human(a_colors[0]);
        this->p2 = new chessgame::Bot(a_colors[1], this->board);
        if(a_colors[0] == chessgame::WHITE) {
            this->p1_king_coord = chessgame::Coordinates{"E1"};
            this->p2_king_coord = chessgame::Coordinates{"E8"};
        }
        else {
            this->p1_king_coord = chessgame::Coordinates{"E8"};
            this->p2_king_coord = chessgame::Coordinates{"E1"};
        }
        this->current_turn = a_colors[0] == chessgame::WHITE; // checking which player is WHITE
        // GUI initialization
        std::cout << "Game created!" << std::endl;
        std::cout << this->board.snapshot() << std::endl;
    }

    Game::Game(bool is_bot_match) : Game() 
    {
        if (is_bot_match) {
            this->is_bot_game = true; // updates flag
            chessgame::PieceColor p1_color = this->p1->getColor();
            delete this->p1; // deletes the old player
            this->p1 = new chessgame::Bot(p1_color, this->board);
        }
    }

    // destructor definition
    Game::~Game()
    {
        if (this->log_file.is_open()) // case: the file should have been closed in play() but it hasn't, so we close it here
            this->log_file.close();
        // delete of raw memory
        delete this->en_passante_coord;
        delete this->p1;
        delete this->p2;
    }

    // private methods definitions
    std::array<chessgame::PieceColor, 2> Game::getRandColors()
    {
        double rand_num = std::rand() % 2; // std library rand function to get a random number (possible values: 0, 1)
        // based on rand_num c_array is initialized with different values (just two possible outcomes, so an if-else is enough to cover them)
        if (rand_num == 0)
            return {chessgame::PieceColor::BLACK, chessgame::PieceColor::WHITE};
        else
            return {chessgame::PieceColor::WHITE, chessgame::PieceColor::BLACK};
    }

    bool Game::isPlayerKingInCheck(const chessgame::Coordinates& king_coord)
    {
        // iterating through the chessboard
        for (int y = 0; y < chessgame::ROWS; y++)
        {
            for (int x = 0; x < chessgame::COLUMNS; x++)
            {
                chessgame::Coordinates piece_coord {x, y};
                chessgame::Piece *p = this->board.get_piece(piece_coord);
                chessgame::PieceColor p_color = this->getCurrentPlayer()->getColor();
                // if it's an opponent's piece, then we check if we're checked by it (one of its possible moves would capture our king)
                if (p != nullptr && p->getColor() != p_color)
                {
                    std::vector<chessgame::Coordinates> moves_vec = this->getPieceMovesAll(piece_coord);
                    // iterators used to check if our king would be captured by a move of the currently analyzed opponent's piece
                    for (auto it = moves_vec.begin(); it != moves_vec.end(); ++it)
                    {
                        if ((*it) == king_coord)
                            return true;
                    }
                }
            }
        }
        return false;
    }

    bool Game::isPlayerKingInCheck() {
        // same as the overloaded version, but here we are providing the current player's king coordinates
        return this->isPlayerKingInCheck(this->getCurrentPlayerKing());
    }

    bool Game::isPawTwoTilesMovement(const std::array<chessgame::Coordinates, 2> &move) 
    {
        chessgame::Piece *p = this->board.get_piece(move[0]);
        if (p == nullptr)
            return false;
        bool p_is_paw = p->getSymbol() == chessgame::BLACK_PAW || p->getSymbol() == chessgame::WHITE_PAW;

        // if we're not moving a paw then there's no meaning to go on
        if (!p_is_paw) return false;

        // other conditions to verify
        bool has_not_moved {!(dynamic_cast<chessgame::Pedone *>(p)->has_already_moved)};
        bool same_column {move[0].x == move[1].x};
        bool offset_is_two {std::abs(move[0].y - move[1].y) == 2};
        bool final_cell_is_empty {this->board.get_piece(move[1]) == nullptr};

        // adjacent cell must be empty too
        chessgame::Coordinates adjacent_coord {move[0].x, move[0].y + (p->getColor() == chessgame::WHITE ? 1 : -1)};
        bool adjacent_cell_empty = this->board.get_piece(adjacent_coord) == nullptr;

        // a first time moving paw is trying to advance by two tiles vertically and there's nothing on its path
        return (p_is_paw && has_not_moved && same_column && offset_is_two && final_cell_is_empty && adjacent_cell_empty);
    }

    bool Game::isEnPassant(char piece_symbol, chessgame::PieceColor p_color, const chessgame::Coordinates &to)
    {
        bool p_is_paw = piece_symbol == chessgame::BLACK_PAW || piece_symbol == chessgame::WHITE_PAW;
        int offset = p_color == chessgame::WHITE ? 1 : -1;
        // en_passant is appliable (last turn a paw has been moved by two tiles) and the piece is a paw that's trying to capture another paw that previously moved by two tiles
        return (this->en_passante_coord != nullptr && p_is_paw && to.x == (this->en_passante_coord)->x && 
            (to.y == (this->en_passante_coord)->y + offset));
    }

    bool Game::isDefaultMove(chessgame::Piece &p, const chessgame::Coordinates &from, const chessgame::Coordinates &to)
    {
        // selected piece's default legal moves
        std::vector<chessgame::Coordinates> legal_moves_vec = p.getMoves(this->board, from);
        for (int i = 0; i < legal_moves_vec.size(); i++)
        {
            if (legal_moves_vec[i] == to)
                return true; // if the move has been found, then it must be valid
        }
        return false;
    }

    void Game::updateFirstMove(const chessgame::Coordinates &coord)
    {
        chessgame::Piece *p = this->board.get_piece(coord);
        if (p == nullptr)
            return; // obviously we can't update the "has_already_moved" flag of a non-existing piece

        // symbol of the piece to update
        const char kPiece_symbol = p->getSymbol();
        if (kPiece_symbol == chessgame::WHITE_KING || kPiece_symbol == chessgame::BLACK_KING)
            dynamic_cast<chessgame::Re *>(p)->has_already_moved = true;
        else if (kPiece_symbol == chessgame::WHITE_PAW || kPiece_symbol == chessgame::BLACK_PAW)
            dynamic_cast<chessgame::Pedone *>(p)->has_already_moved = true;
        else if (kPiece_symbol == chessgame::WHITE_TOWER || kPiece_symbol == chessgame::BLACK_TOWER)
            dynamic_cast<chessgame::Torre *>(p)->has_already_moved = true;
    }

    char Game::promotion(const chessgame::Coordinates &coord)
    {
        // piece to check for promotion
        chessgame::Piece *p = this->board.get_piece(coord);
        // a white paw on the top row or a black paw on the bottom row
        if ((p->getSymbol() == chessgame::WHITE_PAW && coord.y == 7) || (p->getSymbol() == chessgame::BLACK_PAW && coord.y == 0))
        {
            // "asks" the player for the promotion target and proceeds to update the board
            char new_symbol = this->getCurrentPlayer()->getPromotionTarget();
            this->board.promote(new_symbol, coord);
            std::cout << "Paw has been promoted to " << new_symbol << std::endl;
            return new_symbol; // successful promotion
        }
        return 0; // promotion not required
    }

    std::string Game::legalTurnCleanUp(const std::array<chessgame::Coordinates, 2> &move, bool is_arrocco)
    {
        // the log move for the current move
        std::string log_move = move[0].symbol + " " + move[1].symbol;

        if(is_arrocco) {
            // we move move the towers
            chessgame::Coordinates tower_coord;
            if(move[1].x == 6) { // short arrocco
                tower_coord = chessgame::Coordinates{5, move[1].y};
                this->board.swap_positions(tower_coord, chessgame::Coordinates{7, move[1].y});
            }
            else {
                tower_coord = chessgame::Coordinates{3, move[1].y};
                this->board.swap_positions(chessgame::Coordinates{0, move[1].y}, tower_coord);
            }
            this->updateFirstMove(tower_coord); // updates "has_already_moved" flag
        }

        if (this->board.get_piece(move[1]) != nullptr) // this is a capture movement
            this->board.set_piece(move[1], nullptr);
    
        // here the piece is finally moved (swapped)
        this->board.swap_positions(move[0], move[1]);

        // updates "has_already_moved" attribute for paws, kings and towers
        this->updateFirstMove(move[1]);

        char promotion_output = this->promotion(move[1]); // calls the function that manage the special rule "promotion"
        
        if (promotion_output != 0) { // successful promotion, as per documentation
            return (log_move + ' ' + promotion_output); 
        }
        return (log_move + " *");
    }

    std::vector<chessgame::Coordinates> Game::getPieceMovesAll(const chessgame::Coordinates &piece_coord)
    {
        chessgame::Piece *p = this->board.get_piece(piece_coord);
        if (p == nullptr) // a non-existing piece cannot move
            return std::vector<chessgame::Coordinates>{};

        // vector containing all possible moves this piece can do
        std::vector<chessgame::Coordinates> moves_vec = p->getMoves(this->board, piece_coord);

        char p_symbol = p->getSymbol();
        chessgame::PieceColor p_color = p->getColor();

        bool p_is_paw = p_symbol == chessgame::WHITE_PAW || p_symbol == chessgame::BLACK_PAW;

        // two tiles movement of a first time moving paw
        if (p_is_paw && !dynamic_cast<chessgame::Pedone *>(p)->has_already_moved)
        {
            chessgame::Coordinates adjacent_coord {piece_coord.x, piece_coord.y + (p_color == chessgame::WHITE ? 1 : -1)};
            bool adjacent_cell_empty = this->board.get_piece(adjacent_coord) == nullptr;

            int offset = p_color == chessgame::WHITE ? 2 : -2;
            chessgame::Coordinates target_coord {piece_coord.x, piece_coord.y + offset};
            bool path_empty = adjacent_cell_empty && this->board.get_piece(target_coord) == nullptr;
            if(path_empty) {
                moves_vec.push_back(target_coord);
            }
        }

        return moves_vec;
    }

    bool Game::isMoveSelfCheck(const chessgame::Coordinates& from, const chessgame::Coordinates& to, char piece_symbol, bool is_capture, bool is_arrocco) {

        // the king must be forced to not put itself in check, so we need to pass the updated king coordinates to isPlayerKingInCheck()
        chessgame::Coordinates king_coord = getCurrentPlayerKing();
        
        if(is_arrocco) {
            // controllo se il re risulta in scacco nel movimento (quarta condizione per l'arrocco)
            if(to.x == 6) { // short arrocco
                king_coord = {5, to.y};
            }
            else {  // long arrocco
                king_coord = {3, to.y};
            }
            this->board.swap_positions(from, king_coord);
            bool is_invalid = this->isPlayerKingInCheck(king_coord);
            this->board.swap_positions(king_coord, from);
            if(is_invalid)
                return true;
            
            // then we move move the towers
            if(to.x == 6) // short arrocco
                this->board.swap_positions(chessgame::Coordinates{5, from.y}, chessgame::Coordinates{7, from.y});
            else // long arrocco
                this->board.swap_positions(chessgame::Coordinates{0, from.y}, chessgame::Coordinates{3, from.y});
        }

        this->board.swap_positions(from, to); // swaps the two tiles
        if (is_capture)
            this->board.set_piece(from, nullptr); // deletes a piece if it is a capture movement

        if (piece_symbol == chessgame::WHITE_KING || piece_symbol == chessgame::BLACK_KING) // updates the king coordinates if it's a king being moved
            king_coord = to;

        bool is_check = this->isPlayerKingInCheck(king_coord); // checks if the player is still in check

        if (is_capture)
            this->board.restore_setPiece(); // restores the deleted piece if it is a capture movement
        this->board.swap_positions(to, from); // undos the swap

        if(is_arrocco) {
            if(to.x == 6) // short arrocco
                this->board.swap_positions(chessgame::Coordinates{5, from.y}, chessgame::Coordinates{7, from.y});
            else // long arrocco
                this->board.swap_positions(chessgame::Coordinates{0, from.y}, chessgame::Coordinates{3, from.y});
        }

        return is_check;
    }

    bool Game::playerMove(std::array<chessgame::Coordinates, 2> &move)
    {
        chessgame::Piece *p = this->board.get_piece(move[0]);

        // if we're trying to move a non-existing piece obviously it's an invalid move
        if (p != nullptr)
        {
            // symbol of the piece to move
            char piece_symbol = p->getSymbol();

            // booleans used to understand what type of movement it's being made
            bool is_default = this->isDefaultMove(*p, move[0], move[1]);
            bool is_paw_2_tiles_movement = this->isPawTwoTilesMovement(move);
            // arrocco valido solo se il re non è in scacco
            bool is_arrocco = isArrocco(move, this->board) && !this->isPlayerKingInCheck();
            bool is_en_passant = this->isEnPassant(piece_symbol, p->getColor(), move[1]);

            // check if it's one of the valid mvoes (can't do an arrocco if the king is in check)
            bool is_valid_move = is_default || is_paw_2_tiles_movement || is_arrocco || is_en_passant;

            // here move is executed if valid
            if (is_valid_move)
            {
                bool is_capture = this->board.get_piece(move[1]) != nullptr && this->board.get_piece(move[1])->getColor() != p->getColor();
                // self check case, obviously illegal
                if(this->isMoveSelfCheck(move[0], move[1], piece_symbol, is_capture, is_arrocco))
                    return false;
                
                // move is executed and written on the log file
                this->writeLog(this->legalTurnCleanUp(move, is_arrocco));

                // the block below is used for aftereffects and special rules
                // used to reset the EN_PASSANT coordiante setted for a first time moving paw on the next turn
                if(this->en_passante_coord != nullptr) {
                    delete this->en_passante_coord;
                    this->en_passante_coord = nullptr;
                }
                // after effect of paw moving by two tiles
                if(is_paw_2_tiles_movement) {
                    delete this->en_passante_coord;
                    this->en_passante_coord = new chessgame::Coordinates{move[1]};
                }
                
                // we're moving a paw or capturing a piece, so we must reset the stall counter
                if (piece_symbol == chessgame::WHITE_PAW || piece_symbol == chessgame::BLACK_PAW || is_capture)
                    this->stall_counter = 0;

                // updates the player's king position if it has been moved
                if (piece_symbol == chessgame::WHITE_KING || piece_symbol == chessgame::BLACK_KING)
                    this->setCurrentPlayerKing(move[1]);
            }
            return is_valid_move;
        }
        return false;
    }

    bool Game::isGameOver()
    {
        // here the turns have already been swapped. So the current player is the one about to move (at the end of this method)
        chessgame::PieceColor color = this->getCurrentPlayer()->getColor();
        if (this->is_bot_game && this->n_moves >= Game::kBot_moves) // a bot game has reached its maximum amount of moves
        {
            this->writeLog(" * 1\n");
            std::cout << "The full-bot game has reached its maximum amount of moves without ending {" << Game::kBot_moves << "}. Please try again." << std::endl;
            return true;
        }
        else if (this->stall_counter >= 50) // the game is stalled
        {
            this->writeLog(" * 1\n");
            std::cout << "The game ended as 50 consecutive moves has been made without moving a paw or capturing a piece." << std::endl;
            return true;
        }
        else if(!isPlayerKingInCheck()) // player hasn't checked its opponent, but it still might be stalemate
        {
            // block used to check for stalemate
            for (int y = 0; y < chessgame::ROWS; y++)
            {
                for (int x = 0; x < chessgame::COLUMNS; x++)
                {
                    chessgame::Coordinates piece_coord {x, y};
                    chessgame::Piece *p = this->board.get_piece(piece_coord);
                    // a piece of the opponent (now current player) which has moves available
                    if (p != nullptr && p->getColor() == color) {
                        // also it must not be checked by every move available
                        std::vector<chessgame::Coordinates> moves_vec = this->getPieceMovesAll(piece_coord);
                        // N.B.! special rule arrocco can be excluded, if it was available, then the tower must be able to move near the king
                        // this means a move that doesn't check the king must exist if there are the conditions to apply an istance of arrocco
                        if(moves_vec.size() == 0)
                            continue;
                        // iterators are used to check if at least one move exists that unchecks the player
                        for (auto it = moves_vec.begin(); it != moves_vec.end(); ++it)
                        {
                            chessgame::Piece* target_p = this->board.get_piece(*it);

                            bool is_capture = target_p != nullptr && target_p->getColor() != p->getColor();

                            if(!this->isMoveSelfCheck(piece_coord, (*it), p->getSymbol(), is_capture, false)) {
                                this->writeLog(" * 0\n");
                                return false; // it's not a stalemate as we found one legal move to do
                            }
                        }
                    }
                }
            }
            this->writeLog(" * 1\n");
            std::cout << "The game ended as " << (color == chessgame::WHITE ? "WHITE" : "BLACK") << " has been stalemated." << std::endl;
            return true;
        }

        // player has checked its opponent, now we check for a checkmate
        std::cout << (color == chessgame::WHITE ? "WHITE" : "BLACK") << " is in check." << std::endl;
        this->writeLog((color == chessgame::WHITE ? " 0" : " 1"));
        // if current player (the one about to move) is in check: we look if they have moves that uncheck them
        for (int y = 0; y < chessgame::ROWS; y++)
        {
            for (int x = 0; x < chessgame::COLUMNS; x++)
            {
                chessgame::Coordinates piece_coord {x, y};
                chessgame::Piece *p = this->board.get_piece(piece_coord);
                // obviously we only look into pieces belonging to the checked player
                if (p != nullptr && p->getColor() == color)
                {
                    std::vector<chessgame::Coordinates> moves_vec = this->getPieceMovesAll(piece_coord);
                    // iterators are used to theck if at least one move exists that unchecks the player
                    for (auto it = moves_vec.begin(); it != moves_vec.end(); ++it)
                    {
                        chessgame::Piece* target_p = this->board.get_piece(*it);

                        bool is_capture = target_p != nullptr && target_p->getColor() != p->getColor();

                        if(!this->isMoveSelfCheck(piece_coord, (*it), p->getSymbol(), is_capture, false)) {
                            this->writeLog(" 0\n");
                            return false; // it's not checkmate, as we found a move to uncheck the king
                        }
                    }
                }
            }
        }
        std::cout << "It's a checkmate! " << (color == chessgame::WHITE ? "WHITE" : "BLACK") << " lost." << std::endl;
        this->writeLog((color == chessgame::WHITE ? " 3\n" : " 2\n"));
        return true; // game now ends
    }

    // public methods definitions
    void Game::play()
    {
        if(!is_bot_game) std::cout << "Use the command XX XX to print a snapshot of the chessboard." << std::endl;
        this->log_file.open("./game_log.txt"); // opens the log file
        do
        {   
            chessgame::PieceColor color = this->getCurrentPlayer()->getColor();
            std::cout << "\nTurn n.: " << this->n_moves + 1 << (color == chessgame::WHITE ? " - WHITE" : " - BLACK") << " moves." << std::endl;
            bool invalid_move = true;
            do
            {
                // player's move for its turn
                std::array<chessgame::Coordinates, 2> move = this->getCurrentPlayer()->think();
                if(move[0].symbol == "XX" && move[1].symbol == "XX") { // special command as by instructions
                    std::cout << this->board.snapshot() << std::endl;
                    continue;
                }
                invalid_move = !this->playerMove(move);
                if(!invalid_move) {
                    chessgame::Piece* p = this->board.get_piece(move[1]);
                    if(p != nullptr) {
                        std::cout << "-> Moved: " << p->getSymbol() << " from " << move[0].symbol << " to " << move[1].symbol << std::endl;
                    }
                    else std::cout << "ATTENTION: moved from a void tile!" << std::endl; // for debugging purpose
                }
            } while (invalid_move); // this cycle keeps going until a valid move has been entered

            // resets seed generator if bot player
            if(!this->getCurrentPlayer()->is_human)
                dynamic_cast<chessgame::Bot*>(this->getCurrentPlayer())->resetBotSeed();

            this->n_moves++;
            this->stall_counter++;

            std::cout << "********************** End of turn **********************" << std::endl;
    
            this->current_turn = !this->current_turn; // alternates turns
        } while (!isGameOver());
        // snapshot of the state of the chessboard at the end of of the game
        std::cout << this->board.snapshot() << std::endl;
        this->log_file.close(); // closes the log file
    }
}