/*

    @author: Barbato Federico
    @date: 2021-12-27

*/
#include <iostream>
#include "../../include/chessgame/Re.h"

namespace chessgame
{
    /*

        This method returns the possible moves of the piece.
        Offsets are used to set the possible moves of the piece
        and they are calculated in two "for" cicle that scan the adjacent cells of the current piece.

        @arg: const vector<vector<Piece>>&  chessboard of the game
        @arg: const Coordinates &coord coordinates of the current piece

        @return: vector<Coordinates> of the possible moves of the current piece

    */
    vector<Coordinates> Re::getMoves(Chessboard &board, const Coordinates &coord)
    {
        vector<Coordinates> moves;

        int x = coord.x;
        int y = coord.y;

        for (int i = -1; i <= 1; i++)
        {
            for (int j = -1; j <= 1; j++)
            {
                // Control if the end cell is not the piece's cell

                int x_offset = j;
                int y_offset = i;
                // Control if the end cell is in the chessboard
                if (x + x_offset >= 0 && x + x_offset < COLUMNS && y + y_offset >= 0 && y + y_offset < ROWS)
                {
                    if (x_offset == 0 && y_offset == 0)
                    {
                        continue;
                    }
                    else
                    {
                        if (board.get_piece(Coordinates(x + x_offset, y + y_offset)) == nullptr)
                        {
                            moves.push_back(Coordinates(x + x_offset, y + y_offset));
                        }
                        else if (board.get_piece(Coordinates(x + x_offset, y + y_offset))->getColor() != this->getColor())
                        {
                            moves.push_back(Coordinates(x + x_offset, y + y_offset));
                        }
                    }
                }
            }
        }
        return moves;
    }

}