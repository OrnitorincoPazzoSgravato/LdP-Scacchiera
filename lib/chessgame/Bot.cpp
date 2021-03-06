/**
 * @file Bot.cpp
 * @author Enrico Cavinato
 * @brief
 * @version 0.1
 * @date 2022-01-13
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <array>
#include <vector>
#include <ctime>
#include <random>

#include "../../include/chessgame/Bot.h"
#include "../../include/chessgame/Chessboard.h"
#include "../../include/chessgame/Player.h"
#include "../../include/chessgame/Regina.h"
#include "../../include/chessgame/Utilities.h"

namespace chessgame
{
    Coordinates next_cell(const Coordinates &coord)
    {
        //  row ++
        int x{coord.x}, y{coord.y + 1};

        // if end of column, next row
        if (y == ROWS)
        {
            // a caporiga
            y = 0;
            // next column
            x++;
        }
        // if end of matrix
        if (x == COLUMNS)
        {
            // start from the beginning of the matrix
            y = 0;
            x = 0;
        }
        return Coordinates(x, y);
    }

    std::array<Coordinates, 2> Bot::think()
    {
        int count{0};
        // generate coordinates
        Coordinates from = this->starting_tile;

        // while we ispectionate
        while (count < CELLS)
        {

            count++;
            // get piece in from, if empty cell continue
            Piece *p{this->board.get_piece(from)};
            if (!p)
            {
                from = next_cell(from);
                continue;
            }

            PieceColor p_color = p->getColor();
            // if a piece does exist and is controlled by this player
            if (p_color == this->pieceColor)
            {
                starting_tile = from;
                // get possible moves
                std::vector<Coordinates> possible_moves{p->getMoves(this->board, from)};

                char p_symbol{p->getSymbol()};
                bool p_is_paw{p_symbol == chessgame::WHITE_PAW || p_symbol == chessgame::BLACK_PAW};
                bool p_is_king{p_symbol == chessgame::WHITE_KING || p_symbol == chessgame::BLACK_KING};

                // add two tiles move of paw
                if (p_is_paw && !dynamic_cast<Pedone *>(p)->has_already_moved)
                {
                    int offset{p_color == WHITE ? 2 : -2};
                    if ((p_color == WHITE && from.y != 6) || (p_color == BLACK && from.y != 1))
                        possible_moves.push_back(Coordinates{from.x, from.y + offset});
                }
                // add enpassant capture
                else if (p_is_paw)
                {
                    int offset{p_color == WHITE ? 1 : -1};
                    if (from.x != (COLUMNS - 1)) {
                        possible_moves.push_back(Coordinates{from.x + 1, from.y + offset});
                    }
                    if (from.x != 0) {
                        possible_moves.push_back(Coordinates{from.x - 1, from.y + offset});
                    }
                }
                // if p is king and did not move
                else if (p_is_king && !dynamic_cast<Re *>(p)->has_already_moved)
                {
                    //WHITE
                    if (p->getColor() == WHITE)
                    {
                        possible_moves.push_back(white_castling_toleft);
                        possible_moves.push_back(white_castling_toright);
                    }
                    //BLACK
                    possible_moves.push_back(black_castling_toleft);
                    possible_moves.push_back(black_castling_toright);

                }

                // if a possible move does exist
                size_t moves_number{possible_moves.size()};

                if (moves_number != 0)
                {
                    if (last_move_index < 0) // move index must be re-calculated
                    {
                        last_move_index = std::rand() % moves_number;
                    }
                    // if last index exceeds the vector bounds, then it starts again from 0
                    int index{this->last_move_index >= moves_number ? 0 : last_move_index};
                    this->last_move_index = index + 1;
                    this->moves_used++;

                    if (moves_used > moves_number) // tried all moves for this piece, proceeds to the next one (if and when needed)
                    {
                        this->moves_used = 0;
                        this->last_move_index = -1;
                        starting_tile = next_cell(from);
                    }

                    // returns a move
                    Coordinates to{possible_moves[index]};
                    return std::array<Coordinates, 2>{from, to};
                }
            }

            from = next_cell(from);
        }
        // good practice : this function has a defualt move to return: it never occurs because
        // gameplay::Game controls checkmate
        return std::array<Coordinates, 2>{Coordinates{-1, -1}, Coordinates{-1, -1}};
    }

    char Bot::getPromotionTarget()
    {
        if (this->pieceColor == WHITE)
            return WHITE_QUEEN;
        else
            return BLACK_QUEEN;
    }
}