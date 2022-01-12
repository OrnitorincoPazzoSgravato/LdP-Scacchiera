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

#include "../include/chessgame/Bot.h"
#include "../include/chessgame/Utilities.h"
#include "../include/chessgame/Chessboard.h"

namespace gameplay
{

    // constructors declaration
    Game::Game() : n_moves{0}, en_passante_coord{nullptr}, board{chessgame::Chessboard()}, stall_counter{0}
    {
        std::array<chessgame::PieceColor, 2> a_colors = this->getRandColors();
        this->p1 = chessgame::Player(a_colors[0]);
        this->p2 = chessgame::Bot(a_colors[1], this->board);
    }

    Game::Game(bool is_bot_match) : Game()
    {
        if (is_bot_match)
            this->p1 = chessgame::Bot(this->p1.getColor(), this->board);
    }

    // destructor declaration
    Game::~Game()
    {
        if (this->log_file.is_open())
            this->log_file.close();
        delete this->en_passante_coord;
        this->en_passante_coord = nullptr;
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
        this->log_file << move << '\n';
    }

    bool Game::isPlayerKingInCheck(bool player_identifier)
    {
        chessgame::Coordinates king_coord = player_identifier ? this->p1_king_coord : this->p2_king_coord;
        for (int y = 0; y < 8; y++)
        {
            for (int x = 0; x < 8; x++)
            {
                chessgame::Coordinates piece_coord = chessgame::Coordinates(x, y);
                chessgame::Piece *p = this->board.get_piece(piece_coord);
                if (p != nullptr && p->getColor() == (player_identifier ? this->p2.getColor() : this->p1.getColor()))
                {
                    std::vector<chessgame::Coordinates> moves_vec = p->getMoves(this->board, piece_coord);
                    for (auto it = moves_vec.begin(); it != moves_vec.end(); ++it)
                    {
                        if (*it == king_coord)
                            return true;
                    }
                }
            }
        }
        return false;
    }

    bool Game::isPawTwoTilesMovement(const std::array<chessgame::Coordinates, 2> &move)
    {
        chessgame::Piece *p = this->board.get_piece(move[0]);
        if (p == nullptr)
            return false;
        bool p_is_paw = p->getSymbol() == 'p' || p->getSymbol() == 'P';
        if (p_is_paw && !(dynamic_cast<chessgame::Pedone *>(p)->has_already_moved) &&
            move[0].x == move[1].x && std::abs(move[0].y - move[1].y) == 2 &&
            this->board.get_piece(move[1]) == nullptr)
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

    bool Game::isArrocco(const std::array<chessgame::Coordinates, 2> &move)
    {
        chessgame::Piece *p = this->board.get_piece(move[0]);
        if (p == nullptr)
            return false;

        chessgame::Piece *dest_p = this->board.get_piece(move[1]);

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
                bool is_tower_first_move = dynamic_cast<chessgame::Torre *>(king_in_tower ? dest_p : p)->has_already_moved;
                bool is_king_first_move = dynamic_cast<chessgame::Re *>(king_in_tower ? p : dest_p)->has_already_moved;
                if (is_king_first_move && is_tower_first_move)
                {
                    const int kY = move[0].y; // same row as they still have to make a move

                    bool obstacles = false;
                    int index = move[0].x < move[1].x ? move[0].x : move[1].x;
                    int end_index = move[0].x < move[1].x ? move[1].x : move[0].x;
                    for (; index <= end_index && !obstacles; index++)
                    {
                        if (this->board.get_piece(chessgame::Coordinates(kY, index)) != nullptr)
                            obstacles == true;
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

    bool Game::isDefaultMove(chessgame::Piece &p, const chessgame::Coordinates &to)
    {
        // selected piece's default legal moves
        std::vector<chessgame::Coordinates> legal_moves_vec = p.getMoves(this->board, to);
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
        if ((p->getSymbol() == 'p' && coord.x == 0) || (p->getSymbol() == 'P' && coord.x == 7))
        {

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

    std::string Game::legalTurnCleanUp(const std::array<chessgame::Coordinates, 2> &move, bool is_swap)
    {
        // the log move for the current move
        std::string log_move = move[0].symbol + ' ' + move[1].symbol;

        if (!is_swap && this->board.get_piece(move[1]) != nullptr)
        { // this is a capture movement
            this->board.set_piece(move[1], nullptr);
            this->stall_counter = 0;
        }
        // here the piece is finally moved
        this->board.swap_positions(move[0], move[1]);

        // updates "has_already_moved" attribute for paws, kings and towers
        this->updateFirstMove(move[1]);
        if (is_swap)
            this->updateFirstMove(move[0]);

        char promotion_output = this->promotion(move[1]); // calls the function that manage the special rule "promotion"
        if (promotion_output != 0)                        // successful promotion, as per documentation
            log_move += ("\n" + promotion_output);

        return log_move;
    }

    bool Game::playerMove(bool player_identifier, std::array<chessgame::Coordinates, 2> &move)
    {
        chessgame::Piece *p = this->board.get_piece(move[0]);

        // if we're trying to move a non-existing piece obviously it's an invalid move
        if (p != nullptr)
        {
            // symbol of the piece to move
            char piece_symbol = p->getSymbol();

            bool is_default = this->isDefaultMove(*p, move[1]);
            bool is_paw_2_tiles_movement = this->isPawTwoTilesMovement(move);
            bool is_arrocco = this->isArrocco(move);
            bool is_en_passant = this->isEnPassant(p->getSymbol(), move[1]);

            bool is_valid_move = is_default || is_paw_2_tiles_movement || is_arrocco || is_en_passant;

            // here move is executed if valid
            if (is_valid_move)
            {
                // block used to enforce moves on king check
                if (isPlayerKingInCheck(player_identifier))
                {
                    bool is_capture = (is_default && this->board.get_piece(move[1]) != nullptr) || is_en_passant;

                    this->board.swap_positions(move[0], move[1]);
                    if (is_capture)
                        this->board.set_piece(move[0], nullptr);

                    is_valid_move = !this->isPlayerKingInCheck(player_identifier); // checks if the player is still in check

                    if (is_capture)
                        this->board.restore_setPiece();
                    this->board.swap_positions(move[1], move[0]);

                    if (!is_valid_move)
                        return false; // move doesn't resolve the check state, so it's illegal
                }

                // move is executed and written on the log file
                this->writeLog(this->legalTurnCleanUp(move, is_arrocco));

                // the block below is used for clean-up and special rules
                // special rule arrocco: tower in king position case
                if (is_arrocco && (piece_symbol == 't' || piece_symbol == 'T'))
                {
                    player_identifier ? this->p1_king_coord = move[0] : this->p2_king_coord = move[0];
                }
                else if (is_en_passant)
                {
                    delete this->en_passante_coord;
                    this->en_passante_coord = nullptr;
                }
                else if (is_paw_2_tiles_movement)
                {
                    this->en_passante_coord = new chessgame::Coordinates(move[0]);
                }

                if (piece_symbol == 'p' || piece_symbol == 'R')
                {
                    this->stall_counter = 0;
                }

                // updates the player's king position if it has been moved (applied also to special rule: arrocco)
                if (piece_symbol == 'r' || piece_symbol == 'R')
                {
                    player_identifier ? this->p1_king_coord = move[1] : this->p2_king_coord = move[1];
                }
            }
            p = nullptr; // clears p pointer after use
            return is_valid_move;
        }
        return false;
    }

    std::vector<chessgame::Coordinates> Game::getPieceMovesAll(const chessgame::Coordinates &piece_coord)
    {
        chessgame::Piece *p = this->board.get_piece(piece_coord);
        if (p == nullptr)
            return std::vector<chessgame::Coordinates>{};

        // vector containing all possible moves this piece can do (for the king the special move arrocco has been removed, as it has already been considered for an appliable tower)
        std::vector<chessgame::Coordinates> moves_vec = p->getMoves(this->board, piece_coord);

        char p_symbol = p->getSymbol();

        bool p_is_paw = p_symbol == 'p' || p_symbol == 'P';
        bool p_is_tower = p_symbol == 't' || p_symbol == 'T';
        // two tiles movement of a first time moving paw
        if (p_is_paw && !dynamic_cast<chessgame::Pedone *>(p)->has_already_moved)
        {
            int offset = p->getColor() == chessgame::WHITE ? 2 : -2;
            moves_vec.push_back(chessgame::Coordinates(piece_coord.x, piece_coord.y + offset));
        }
        // en passant capture
        else if (p_is_paw && this->en_passante_coord != nullptr)
        {
            int offset = p->getColor() == chessgame::WHITE ? 1 : -1;
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
            chessgame::Coordinates king_coord = p->getColor() == this->p1.getColor() ? p1_king_coord : p2_king_coord;
            if (!dynamic_cast<chessgame::Re *>(this->board.get_piece(king_coord))->has_already_moved)
            {
                moves_vec.push_back(king_coord);
            }
        }
        // king in tower arrocco has been skipped as it's the same as a tower in king arrocco
        return moves_vec;
    }

    bool Game::isGameOver()
    {
        // block used to check if a bot game has reached its max amount of moves (game ending condition)
        if (this->n_moves >= Game::kBot_moves)
        {
            std::cout << "The full-bot game has reached its maximum amount of moves without ending {" << Game::kBot_moves << "}. Please try again." << std::endl;
            return true;
        }
        if (this->stall_counter >= 50)
        {
            std::cout << "The game ended as 50 consecutive moves has been made without moving a paw or capturing a piece." << std::endl;
            return true;
        }
        if (!isPlayerKingInCheck(!this->current_turn))
        {
            // block used to check for stalemate
            for (int y = 0; y < 8; y++)
            {
                for (int x = 0; x < 8; x++)
                {
                    chessgame::Coordinates piece_coord = chessgame::Coordinates(x, y);
                    chessgame::Piece *p = this->board.get_piece(piece_coord);
                    if (p != nullptr && p->getColor() == (this->current_turn ? this->p2.getColor() : this->p1.getColor()))
                    {
                        if (this->getPieceMovesAll(piece_coord).size() != 0)
                            return false;
                    }
                }
            }
        }

        // check is it's checkmate
        for (int y = 0; y < 8; y++)
        {
            for (int x = 0; x < 8; x++)
            {
                chessgame::Coordinates piece_coord = chessgame::Coordinates(x, y);
                chessgame::Piece *p = this->board.get_piece(piece_coord);

                if (p != nullptr && p->getColor() == (this->current_turn ? this->p2.getColor() : this->p1.getColor()))
                {
                    std::vector<chessgame::Coordinates> moves_vec = this->getPieceMovesAll(piece_coord);

                    for (auto it = moves_vec.begin(); it != moves_vec.end(); ++it)
                    {

                        bool is_capture = this->board.get_piece(*it)->getSymbol() != p->getSymbol(); // surely not nullptr by how the code is structored

                        this->board.swap_positions(piece_coord, *it);
                        if (is_capture)
                            this->board.set_piece(piece_coord, nullptr);

                        bool check_resolved = !this->isPlayerKingInCheck(!this->current_turn); // checks if the player is still in check

                        if (is_capture)
                            this->board.restore_setPiece();
                        this->board.swap_positions(*it, piece_coord);

                        if (check_resolved)
                            return false; // move doesn't resolve the check state, so it's illegal
                    }
                }
            }
        }

        return true;
    }

    // public methods declaration
    void Game::play()
    {
        this->log_file.open("game_log.txt"); // open the log file

        do
        {
            bool invalid_move = true;
            do
            {
                // player's move for its turn
                std::array<chessgame::Coordinates, 2> move = this->current_turn ? this->p1.think() : this->p2.think();
                invalid_move = this->playerMove(this->current_turn, move);

            } while (invalid_move); // this cycle keeps going until a valid move has been entered

            std::cout << this->board.snapshot() << '\n';

            this->n_moves++; // increse number of moves
            this->stall_counter++;

            this->current_turn = !this->current_turn; // alternates turns
        } while (!isGameOver());

        this->log_file.close(); // closes the log file
    }
}