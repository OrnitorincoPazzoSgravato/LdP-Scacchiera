/*

    @author: Federico Barbato
    @date: 2021-12-27

*/
#include <iostream>
#include "../../include/chessgame/Cavallo.h"

namespace chessgame
{

    Cavallo::Cavallo(PieceColor color, const char symbol) : Piece(color, symbol)
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
    vector<Coordinates> Cavallo::getMoves(Chessboard &board, const Coordinates &coord)
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
            if (x + x_offset >= 0 && x + x_offset < ROWS && y + y_offset >= 0 && y + y_offset < COLUMNS)
            {
                if (board.get_piece(Coordinates(x + x_offset, y + y_offset)) == nullptr)
                {
                    moves.push_back(Coordinates(x + x_offset, y + y_offset));
                }
                else
                {
                    // Control if the end cell is an enemy
                    if (board.get_piece(Coordinates(x + x_offset, y + y_offset))->getColor() != this->getColor())
                    {
                        moves.push_back(Coordinates(x + x_offset, y + y_offset));
                    }
                }
            }
        }

        for (auto &move : moves)
        {
            std::cout << "Cavallo Move: " << move.x << " " << move.y << std::endl;
        }

        return moves;
    }

}