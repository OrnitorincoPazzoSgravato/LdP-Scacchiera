/*

    @author: Federico Barbato
    @date: 2021-12-27

*/

#include "../include/Cavallo.h"

namespace chessgame
{

    Cavallo::Cavallo(PieceColor color, const char symbol) : Piece(color, symbol)
    {
    }

    Cavallo::Cavallo() : Piece()
    {
    }

    /*

        This method returns the possible moves of the piece.
        Offsets are used to set the possible moves of the piece
        and they are organized in a matrix made up of all possible combinations of the offsets.

        @arg: const vector<vector<Piece>>&  chessboard of the game
        @arg: const Coordinates &coord coordinates of the current piece

        @return: vector<Coordinates> of the possible moves of the current piece

    */
    vector<Coordinates> Cavallo::getMoves(Chessboard *board, const Coordinates &coord)
    {
        vector<Coordinates> moves;

        int x = coord.x;
        int y = coord.y;

        // Matrix of the offsets
        int offsets[8][2]{
            {1, 2},
            {2, 1},
            {2, -1},
            {1, -2},
            {-1, -2},
            {-2, -1},
            {-2, 1},
            {-1, 2}};

        //Foreach couple of offsets
        for (auto &offset : offsets)
        {
            int x_offset = offset[0];
            int y_offset = offset[1];

            // Control if the end cell is in the chessboard
            if (x + x_offset >= 0 && y + y_offset < 8 && y + y_offset >= 0 && y + y_offset < 8)
            {
                // Control if the end cell is not the same color of the current piece
                if (board->get_piece(Coordinates(x + x_offset, y + y_offset))->getColor() != this->color)
                {
                    // If not than add the move to the move vector
                    moves.push_back(Coordinates(x + x_offset, y + y_offset));
                }
            }
        }

        return moves;
    }

}