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
#include <stdexcept>
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
        int x {coord.x}, y {coord.y + 1};

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
        Coordinates from{std::rand() % ROWS, std::rand() % COLUMNS};

        // while we ispectionate
        while (count < CELLS)
        {
            count++;
            // next cell
            from = next_cell(from);

            // get piece in from, if empty cell continue
            Piece *p{this->board.get_piece(from)};
            if (!p)
                continue; 

            // if a piece does exist and is controlled by this player
            if (p->getColor() == this->pieceColor)
            {

                // get possible moves
                std::vector<Coordinates> possible_moves{p->getMoves(this->board, from)};

                // if a possible move does exist
                size_t moves_number{possible_moves.size()};
                if (moves_number != 0)
                {
                    int index = this->last_move_index >= moves_number ? std::rand() % moves_number : this->last_move_index;
                    this->last_move_index = index + 1;
                    // returns a move
                    Coordinates to{possible_moves[index]};
                    return std::array<Coordinates, 2>{from, to};
                }
            }
        }
        // good practice : this function has a defualt move to return: it never occurs because 
        // gameplay::Game controls checkmate
        return std::array<Coordinates,2> {Coordinates {-1,-1},Coordinates {-1,-1}};
    }

    char Bot::getPromotionTarget()
    {
        if (this->pieceColor == WHITE)
            return WHITE_QUEEN;
        else
            return BLACK_QUEEN;
    }
}