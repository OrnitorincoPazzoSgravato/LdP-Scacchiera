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

    // constructors declaration
    Game::Game() : n_moves{0}, en_passante_coord{nullptr}, board{chessgame::Chessboard()}, stall_counter{0}, is_bot_game{false}
    {
        srand(time(NULL)); // used to randomize each game
        std::array<chessgame::PieceColor, 2> a_colors = this->getRandColors();
        this->p1 = new chessgame::Human(a_colors[0]);
        this->p2 = new chessgame::Bot(a_colors[1], this->board);
        if(a_colors[0] == chessgame::WHITE) {
            this->p1_king_coord = chessgame::Coordinates("E1");
            this->p2_king_coord = chessgame::Coordinates("E8");
        }
        else {
            this->p1_king_coord = chessgame::Coordinates("E8");
            this->p2_king_coord = chessgame::Coordinates("E1");
        }
        this->current_turn = a_colors[0] == chessgame::WHITE;
        std::cout << "Game created!" << std::endl;
        std::cout << this->board.snapshot() << std::endl;
    }

    Game::Game(bool is_bot_match) : Game()
    {
        if (is_bot_match) {
            this->is_bot_game = true;
            chessgame::PieceColor p1_color = this->p1->getColor();
            delete this->p1;
            this->p1 = new chessgame::Bot(p1_color, this->board);
        }
    }

    // destructor declaration
    Game::~Game()
    {
        if (this->log_file.is_open())
            this->log_file.close();
        delete this->en_passante_coord;
        delete this->p1;
        delete this->p2;
    }

    // private methods declaration
    std::array<chessgame::PieceColor, 2> Game::getRandColors()
    {
        std::array<chessgame::PieceColor, 2> c_array; // declaration of the returned array

        double rand_num = std::rand(); // std library rand function to get a random number between 0 and 1
        // based on rand_num c_array is initialized with different values (just two possible outcomes, so an if-else is enough to cover them)
        if (rand_num < 0.5)
            c_array = {chessgame::PieceColor::BLACK, chessgame::PieceColor::WHITE};
        else
            c_array = {chessgame::PieceColor::WHITE, chessgame::PieceColor::BLACK};
        return c_array;
    }

    void Game::writeLog(const std::string &move)
    {
        this->log_file << move << std::endl;
    }

    bool Game::isPlayerKingInCheck(const chessgame::Coordinates king_coord)
    {
        for (int y = 0; y < 8; y++)
        {
            for (int x = 0; x < 8; x++)
            {
                chessgame::Coordinates piece_coord = chessgame::Coordinates(x, y);
                chessgame::Piece *p = this->board.get_piece(piece_coord);
                chessgame::PieceColor p_color = this->getCurrentPlayer()->getColor();
                if (p != nullptr && p->getColor() != p_color)
                {
                    std::vector<chessgame::Coordinates> moves_vec = p->getMoves(this->board, piece_coord);
                    for (auto it = moves_vec.begin(); it != moves_vec.end(); ++it)
                    {
                        if ((*it).x == king_coord.x && (*it).y == king_coord.y) {
                            return true;
                        }
                    }
                }
            }
        }
        return false;
    }

    bool Game::isPlayerKingInCheck() {
        return this->isPlayerKingInCheck(this->getCurrentPlayerKing());
    }

    bool Game::isPawTwoTilesMovement(const std::array<chessgame::Coordinates, 2> &move)
    {
        chessgame::Piece *p = this->board.get_piece(move[0]);
        if (p == nullptr)
            return false;
        bool p_is_paw = p->getSymbol() == 'p' || p->getSymbol() == 'P';

        // se non è un pedone
        if (!p_is_paw) return false;

        // conditions to verify
        bool has_moved {(dynamic_cast<chessgame::Pedone *>(p)->has_already_moved)};
        bool same_column {move[0].x == move[1].x};
        bool y_offset_is_two {std::abs(move[0].y - move[1].y) == 2};
        bool final_cell_is_empty {this->board.get_piece(move[1]) == nullptr};

        if (p_is_paw && !has_moved && same_column && y_offset_is_two && final_cell_is_empty)
            //&& !(dynamic_cast<chessgame::Pedone *>(p)->has_already_moved) &&
            //move[0].x == move[1].x && std::abs(move[0].y - move[1].y) == 2 &&
            //this->board.get_piece(move[1]) == nullptr)
        {
            p = nullptr;
            return true;
        }
        p = nullptr;
        return false;
    }

    bool Game::isEnPassant(char piece_symbol, const chessgame::Coordinates &to)
    {
        bool p_is_paw = piece_symbol == 'p' || piece_symbol == 'P';
        // en_passant is appliable
        if (this->en_passante_coord != nullptr)
        {
            // it's a paw trying to capture another paw that previously moved by two tiles
            return (p_is_paw && to == *(this->en_passante_coord));
        }
        return false;
    }

    bool isArrocco(const std::array<chessgame::Coordinates, 2> &move, const chessgame::Chessboard &board)
    {
        chessgame::Piece *p = board.get_piece(move[0]);
        if (p == nullptr)
            return false;

        chessgame::Piece *dest_p = board.get_piece(move[1]);

        char piece_symbol = p->getSymbol();

        if (dest_p != nullptr && p->getColor() == dest_p->getColor())
        { // not a nullptr and same color
            const char kDest_p_symbol = dest_p->getSymbol();
            bool p_Is_King = piece_symbol == 'r' || piece_symbol == 'R';
            bool p_Is_Tower = piece_symbol == 't' || piece_symbol == 'T';
            bool dest_Is_King = kDest_p_symbol == 'r' || kDest_p_symbol == 'R';
            bool dest_Is_Tower = kDest_p_symbol == 't' || kDest_p_symbol == 'r';

            bool king_in_tower = p_Is_King && dest_Is_Tower;
            bool tower_in_king = p_Is_Tower && dest_Is_King;

            if (king_in_tower || tower_in_king)
            {
                // the conditional operator is used to differentiate between king or tower istance as the object pointed by p (and so dest_p)
                bool is_tower_first_move = !dynamic_cast<chessgame::Torre *>(king_in_tower ? dest_p : p)->has_already_moved;
                bool is_king_first_move = !dynamic_cast<chessgame::Re *>(king_in_tower ? p : dest_p)->has_already_moved;
                if (is_king_first_move && is_tower_first_move)
                {
                    const int kY = move[0].y; // same row as they still have to make a move

                    bool obstacles = false;
                    int index = move[0].x < move[1].x ? move[0].x : move[1].x;
                    int end_index = move[0].x < move[1].x ? move[1].x : move[0].x;
                    for (; index <= end_index && !obstacles; index++)
                    {
                        if (board.get_piece(chessgame::Coordinates(kY, index)) != nullptr)
                            obstacles == true;
                    }

                    // if there are no obstacles then the special rule is legal
                    return !obstacles;
                }
            }
        }

        return false;
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
            return;
        // symbol of the piece to update
        const char kPiece_symbol = p->getSymbol();
        if (kPiece_symbol == 'r' || kPiece_symbol == 'R')
            dynamic_cast<chessgame::Re *>(p)->has_already_moved = true;
        else if (kPiece_symbol == 'p' || kPiece_symbol == 'P')
            dynamic_cast<chessgame::Pedone *>(p)->has_already_moved = true;
        else if (kPiece_symbol == 't' || kPiece_symbol == 'T')
            dynamic_cast<chessgame::Torre *>(p)->has_already_moved = true;
        p = nullptr;
    }

    char Game::promotion(const chessgame::Coordinates &coord)
    {
        // piece to check for promotion
        chessgame::Piece *p = this->board.get_piece(coord);
        // a white paw on the top row or a black paw on the bottom row
        if ((p->getSymbol() == 'p' && coord.y == 7) || (p->getSymbol() == 'P' && coord.y == 0))
        {
            p = nullptr;
            // "asks" the player for the promotion target and proceeds to update the board
            char new_symbol = this->getCurrentPlayer()->getPromotionTarget();
            this->board.promote(new_symbol, coord);
            std::cout << "Paw has been promoted to " << new_symbol << std::endl;
            return new_symbol; // successful promotion
        }
        return 0; // promotion not required
    }

    std::string Game::legalTurnCleanUp(const std::array<chessgame::Coordinates, 2> &move, bool is_swap)
    {
        // the log move for the current move
        std::string log_move = move[0].symbol + " " + move[1].symbol;

        if (!is_swap && this->board.get_piece(move[1]) != nullptr)
        { // this is a capture movement
            this->board.set_piece(move[1], nullptr);
        }
        // here the piece is finally moved
        this->board.swap_positions(move[0], move[1]);

        // updates "has_already_moved" attribute for paws, kings and towers
        this->updateFirstMove(move[1]);
        if (is_swap)
            this->updateFirstMove(move[0]);

        char promotion_output = this->promotion(move[1]); // calls the function that manage the special rule "promotion"
        
        if (promotion_output != 0) { // successful promotion, as per documentation
            return (log_move + ' ' + promotion_output); 
        }
        else return (log_move + " *");

        return log_move;
    }

    std::vector<chessgame::Coordinates> Game::getPieceMovesAll(const chessgame::Coordinates &piece_coord)
    {
        chessgame::Piece *p = this->board.get_piece(piece_coord);
        if (p == nullptr)
            return std::vector<chessgame::Coordinates>{};

        // vector containing all possible moves this piece can do
        std::vector<chessgame::Coordinates> moves_vec = p->getMoves(this->board, piece_coord);

        char p_symbol = p->getSymbol();
        chessgame::PieceColor p_color = p->getColor();

        bool p_is_paw = p_symbol == 'p' || p_symbol == 'P';
        bool p_is_tower = p_symbol == 't' || p_symbol == 'T';
        bool p_is_king = p_symbol == 'r' || p_symbol == 'R';
        // two tiles movement of a first time moving paw
        if (p_is_paw && !dynamic_cast<chessgame::Pedone *>(p)->has_already_moved)
        {
            int offset = p_color == chessgame::WHITE ? 2 : -2;
            moves_vec.push_back(chessgame::Coordinates(piece_coord.x, piece_coord.y + offset));
        }
        // en passant capture
        else if (p_is_paw && this->en_passante_coord != nullptr && this->board.get_piece(*(this->en_passante_coord))->getColor() != p_color)
        {
            int offset = p_color == chessgame::WHITE ? 1 : -1;
            bool left_capturable = *(this->en_passante_coord) == chessgame::Coordinates(piece_coord.x - 1, piece_coord.y + offset);
            bool right_capturable = *(this->en_passante_coord) == chessgame::Coordinates(piece_coord.x + 1, piece_coord.y + offset);
            if (left_capturable)
                moves_vec.push_back(chessgame::Coordinates(piece_coord.x - 1, piece_coord.y + offset));
            else if (right_capturable)
                moves_vec.push_back(chessgame::Coordinates(piece_coord.x + 1, piece_coord.y + offset));
        }
        // tower in king arrocco
        else if (p_is_tower && !dynamic_cast<chessgame::Torre *>(p)->has_already_moved)
        {
            chessgame::Coordinates king_coord = p_color == this->p1->getColor() ? p1_king_coord : p2_king_coord;
            if (!dynamic_cast<chessgame::Re *>(this->board.get_piece(king_coord))->has_already_moved)
            {
                moves_vec.push_back(king_coord);
            }
        }
        // king in tower arrocco
        else if(p_is_king && !dynamic_cast<chessgame::Re *>(p)->has_already_moved) {
            int t_y = piece_coord.y;
            std::array<chessgame::Coordinates, 2> a {chessgame::Coordinates{7, t_y}, chessgame::Coordinates{0, t_y}};
            for(int i = 0; i < 2; i++) {
                chessgame::Piece* tower = this->board.get_piece(a[i]);
                bool is_same_color = tower != nullptr && tower->getColor() == p_color;
                bool is_valid_tower = is_same_color && (tower->getSymbol() == 't' || tower->getSymbol() == 'T') &&
                !dynamic_cast<chessgame::Torre *>(tower)->has_already_moved;
                if(is_valid_tower) moves_vec.push_back(a[i]);
            }
        }
        return moves_vec;
    }

    bool Game::isMoveSelfCheck(const chessgame::Coordinates& from, const chessgame::Coordinates& to, char piece_symbol, bool is_capture, bool is_arrocco) {
        bool invalid_move = true;

        this->board.swap_positions(from, to);
        if (is_capture)
            this->board.set_piece(from, nullptr);

        // i must also prohibit the king from placing himself on check
        chessgame::Coordinates king_coord = getCurrentPlayerKing();
        if (piece_symbol == 'r' || piece_symbol == 'R')
            king_coord = to;
        else if(is_arrocco)
            king_coord = from;

        invalid_move = this->isPlayerKingInCheck(king_coord); // checks if the player is in check

        if (is_capture)
            this->board.restore_setPiece();
        this->board.swap_positions(to, from);

        return invalid_move;
    }

    bool Game::playerMove(std::array<chessgame::Coordinates, 2> &move)
    {
        chessgame::Piece *p = this->board.get_piece(move[0]);

        // if we're trying to move a non-existing piece obviously it's an invalid move
        if (p != nullptr)
        {
            // symbol of the piece to move
            char piece_symbol = p->getSymbol();

            bool is_default = this->isDefaultMove(*p, move[0], move[1]);
            bool is_paw_2_tiles_movement = this->isPawTwoTilesMovement(move);
            bool is_arrocco = isArrocco(move, this->board);
            bool is_en_passant = this->isEnPassant(p->getSymbol(), move[1]);

            bool is_valid_move = is_default || is_paw_2_tiles_movement || is_arrocco || is_en_passant;

            // here move is executed if valid
            if (is_valid_move)
            {
                bool is_capture = (is_default && this->board.get_piece(move[1]) != nullptr) || is_en_passant;
                // self check case, obviously illegal
                if(this->isMoveSelfCheck(move[0], move[1], piece_symbol, is_capture, is_arrocco))
                    return false;
                
                // move is executed and written on the log file
                this->writeLog(this->legalTurnCleanUp(move, is_arrocco));

                // the block below is used for aftereffects and special rules
                // special rule arrocco: tower in king position case
                if (is_arrocco && (piece_symbol == 't' || piece_symbol == 'T'))
                    this->setCurrentPlayerKing(move[0]);
                else if (is_en_passant)
                {
                    delete this->en_passante_coord;
                    this->en_passante_coord = nullptr;
                }
                else if (is_paw_2_tiles_movement) {
                    delete this->en_passante_coord;
                    this->en_passante_coord = new chessgame::Coordinates(move[1]);
                }

                // we're moving a paw or capturing a piece, so we must reset the stall counter
                if (piece_symbol == 'p' || piece_symbol == 'P' || is_capture)
                    this->stall_counter = 0;

                // updates the player's king position if it has been moved (except for tower in king arrocco)
                if (piece_symbol == 'r' || piece_symbol == 'R')
                    this->setCurrentPlayerKing(move[1]);
            }
            return is_valid_move;
        }
        return false;
    }

    bool Game::isGameOver()
    {
        chessgame::PieceColor color = this->getCurrentPlayer()->getColor();
        if (this->is_bot_game && this->n_moves >= Game::kBot_moves) // a bot game has reached its maximum amount of moves
        {
            std::cout << "The full-bot game has reached its maximum amount of moves without ending {" << Game::kBot_moves << "}. Please try again." << std::endl;
            return true;
        }
        else if (this->stall_counter >= 50) // the game is stalled
        {
            std::cout << "The game ended as 50 consecutive moves has been made without moving a paw or capturing a piece." << std::endl;
            return true;
        }
        else if(!isPlayerKingInCheck()) // player hasn't checked its opponent, but it still might be stalemate
        {
            // block used to check for stalemate
            for (int y = 0; y < 8; y++)
            {
                for (int x = 0; x < 8; x++)
                {
                    chessgame::Coordinates piece_coord = chessgame::Coordinates(x, y);
                    chessgame::Piece *p = this->board.get_piece(piece_coord);
                    if (p != nullptr && p->getColor() == color)
                    {
                        if (this->getPieceMovesAll(piece_coord).size() != 0)
                            return false;
                    }
                }
            }
            return true;
        }

        // player has checked its opponent, now we check for a checkmate
        std::cout << (color == chessgame::WHITE ? "WHITE" : "BLACK") << " is in check." << std::endl;
        // if WHITE is in check, we should look if they have moves that uncheck them
        for (int y = 0; y < 8; y++)
        {
            for (int x = 0; x < 8; x++)
            {
                chessgame::Coordinates piece_coord = chessgame::Coordinates(x, y);
                chessgame::Piece *p = this->board.get_piece(piece_coord);

                if (p != nullptr && p->getColor() == color)
                {
                    std::vector<chessgame::Coordinates> moves_vec = this->getPieceMovesAll(piece_coord);

                    for (auto it = moves_vec.begin(); it != moves_vec.end(); ++it)
                    {
                        chessgame::Piece* target_p = this->board.get_piece(*it);

                        bool is_capture = target_p != nullptr && target_p->getSymbol() != p->getSymbol();
                        bool is_arrocco = isArrocco(std::array<chessgame::Coordinates, 2> {piece_coord, *it}, this->board);

                        if(!this->isMoveSelfCheck(piece_coord, (*it), p->getSymbol(), is_capture, is_arrocco)) {
                            return false;
                        }
                    }
                }
            }
        }
        
        std::cout << "It's a checkmate! " << (color == chessgame::WHITE ? "WHITE" : "BLACK") << " lost." << std::endl;
        return true;
    }

    // public methods declaration
    void Game::play()
    {
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
                invalid_move = !this->playerMove(move);
                if(!invalid_move) {
                    chessgame::Piece* p = this->board.get_piece(move[1]);
                    if(p != nullptr) {
                        std::cout << "Moved: " << p->getSymbol() << " from " << move[0].symbol << " to " << move[1].symbol << std::endl;
                    }
                    else std::cout << "ATTENTION: moved from a void tile!" << std::endl; // for debugging
                }
            } while (invalid_move); // this cycle keeps going until a valid move has been entered

            this->n_moves++; // increse number of moves
            this->stall_counter++;
            std::cout << this->board.snapshot() << std::endl;
            std::cout << "********************** End of turn **********************" << std::endl;
            this->current_turn = !this->current_turn; // alternates turns
        } while (!isGameOver());

        this->log_file.close(); // closes the log file
    }
}