/*

    @author: Enrico Cavinato
    @date: 2021-12-29

*/

#include <random>
#include <array>
#include <vector>

#include "../../include/chessgame/Bot.h"
#include "../../include/chessgame/Chessboard.h"

namespace chessgame
{
    std::array<Coordinates, 2> &Bot::think()
    {
        // generate the coordinates of a random cell we want to visit
        int row{std::rand() % ROWS};
        int column{std::rand() % COLUMNS};

        // number of visited cells set to 0
        int visited_cells{0};

        // while loop visit every piece of given color and considers its possible moves
        bool done{false};

        //Coordinates we start from
        Coordinates from;

        // while loop visit all valid cells
        while (from.x != -1)
        {
            // get almost random Coordinates of a piece of given color
            // count is passed by reference because we want get() function to modify it
            from = this->board.get_random(pieceColor, Coordinates(column, row), visited_cells);

            // get the possible moves
            std::vector<Coordinates> possible_moves{this->board.get_piece(from)->getMoves(this->board, from)};

            // if a possible move does not exist
            if (possible_moves.size() == 0)
            {
                // continue the loop but get() will continue to iterate the matrix from the cell where it stopped at the previous iteration
                row = from.y;
                column = from.x + 1;
                continue;
            }

            // if a possible move does exist
            Coordinates to{possible_moves[0]};
            return std::array<Coordinates, 2>{from, to};
        }
    }
    Piece *Bot::getPromotionTarget()
    {
        char c = '0';
        if (pieceColor == WHITE)
            c = 'd';
        else
            c = 'D';
        return &Regina(pieceColor, c);
    }
}