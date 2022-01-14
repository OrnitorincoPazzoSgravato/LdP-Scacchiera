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

#include "../../include/chessgame/Bot.h"
#include "../../include/chessgame/Chessboard.h"
#include "../../include/chessgame/Player.h"
#include "../../include/chessgame/Regina.h"

namespace chessgame
{
    /**
     * @brief This helper function generate a row ( it is not random : it starts form the paw line)
     * 
     * @param pc the color of paws
     * @return int the number of a row or column
     */
    int generate_row(PieceColor pc)
    {
        if (pc == WHITE)  return 1;
        return 6;        
    }
    /**
     * @brief iterate a coordinate
     * 
     * @param coord the coordinate
     */
    Coordinates Bot::next_cell(const Coordinates& coord)
    {
        // column ++
        int x = coord.x + 1;
        int y = coord.y;
        // if end of column, next row
        if (x == COLUMNS)
        {
            // a caporiga
            x = 0;
            // next row
            y++;
        }
        // if end of matrix
        if (y == ROWS && x == COLUMNS)
        {
            // start from the beginning
            y = 0;
            x = 0;
        }
        return Coordinates(x, y);
    }

    std::array<Coordinates, 2> Bot::think()
    {
        // generate row,column, and count
        int row {generate_row(pieceColor)};
        // std::cout << "Raw generated :  "<< row  << "\n";
        int column {std::rand() % COLUMNS};
        // std::cout << "Column generated :  "<< column  << "\n";
        int count {0};

        //generate coordinate
        Coordinates from {column,row};

        //while we ispectionate
        while (count < CELLS)
        {
            count++;
            // next cell
            from = next_cell(from);

            // get piece in from
            Piece *p {this->board.get_piece(from)};

            // if a piece does exist and is controlled by this player
            if ( p && p->getColor() == this->pieceColor)
            {

                // get possible moves
                std::vector<Coordinates> possible_moves{p->getMoves(this->board,from)};

                // if a possible move does exist
                int moves_number {possible_moves.size()};
                if (moves_number != 0)
                {
                    std::cout << "Moving: "<< from.symbol << '\n';
                    // returns the first move
                    Coordinates to {possible_moves[0]};
                    return std::array<Coordinates,2> {from, to};
                }
            }    
        }
    }


    char Bot::getPromotionTarget()
    {
        char c = '0';
        if (this->pieceColor == WHITE) c = 'd';
        else c = 'D';
        return c;
    }
}