/*

    @author: Enrico Cavinato
    @date: 2021-12-29

*/

#include <random>
#include <array>
#include <vector>

#include "../include/Bot.h"

namespace chessgame
{
    Bot::Bot() : Player() {}
    Bot::Bot(const PieceColor& p_color) : Player(p_color) 
    {}
    std::array<Coordinates,2>& Bot::think(Chessboard& board) 
    {
        // generate the coordinates of a random cell we want to inspectionate
        int row {std::rand() % ROWS};
        int column {std::rand() % COLUMNS};
        // while loop visit every piece of given color and considers its possible moves
        bool done {false};
        while (!done)
        {
            // get almost random Coordinates of a piece of given color
            Coordinates from {board.get(pieceColor,row,column,0)};
            // get the possible moves
            std::vector<Coordinates> possible_moves {board.get_piece(from)->getMoves(board,from)};
            // if a possible move does not exist
            if (possible_moves.size() == 0) 
            {
                // continue the loop but get() will continue to iterate the matrix from the cell where it stopped at the previous iteration
                row = from.y;
                column = from.x +1;
                continue;
            }
            // if a possible move does exist
            Coordinates to {possible_moves[0]};
            return std::array<Coordinates,2> {from,to};
        }
    }
    Piece* Bot::getPromotionTarget() {
        char c = '0';
        if (pieceColor == WHITE) c = 'd';
        else c = 'D'; 
        return new Regina(pieceColor,c);
    }
}