/*

    @author: Barbato Federico
    @date: 2021-12-27

*/
#include "../include/Re.h"

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

        for (int i = -1; i < 2; i++)
        {
            for (int j = -1; j < 2; j++)
            {
                // Control if the end cell is not the piece's cell
                if (i != 0 && j != 0)
                {
                    int x_offset = i;
                    int y_offset = j;

                    // Control if the end cell is in the chessboard
                    if (x + x_offset >= 0 && x + x_offset < COLUMNS && y + y_offset >= 0 && y + y_offset < ROWS)
                    {
                        // Control if the end cell is not the same color of the current piece
                        if (board.get_piece(Coordinates(x + x_offset, y + y_offset))->getColor() != this->getColor())
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