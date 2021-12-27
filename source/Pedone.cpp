/*

    @author: Federico Barbato
    @date: 2021-12-27

*/

#include "../include/Pedone.h"

namespace chessgame
{
    Pedone::Pedone(PieceColor color, const char symbol) : Piece(color, symbol)
    {
    }

    vector<Coordinates> Pedone::getMoves(const vector<vector<Piece>> &board, int x, int y)
    {
        vector<Coordinates> moves;
        int x_offset = 0;
        int y_offset = 0;

        if (this->color == PieceColor::WHITE)
        {
            x_offset = -1;
            y_offset = -1;
        }
        else
        {
            x_offset = 1;
            y_offset = 1;
        }

        // Control if the y move is inside the board
        if (y + y_offset >= 0 && y + y_offset < 8)
        {
            // Control if the end position is empty (only vertical movement)
            if (board[y + y_offset][x] == nullptr)
            {
                moves.push_back(Coordinates(x + x_offset, y + y_offset));
            }

            // Control if the x move is inside the board
            if (x + x_offset >= 0 && x + x_offset < 8)
            {

                // Control if the end position is an enemy (only diagonal movement)

                if (board[y + y_offset][x + x_offset].getColor() != this->color && board[y + y_offset][x + x_offset] != 0)
                {
                    moves.push_back(Coordinates(x + x_offset, y + y_offset));
                }
            }

            if (x - x_offset >= 0 && x - x_offset < 8)
            {

                // Control if the end position is an enemy (only diagonal movement)

                if (board[y + y_offset][x - x_offset].getColor() != this->color && board[y + y_offset][x - x_offset] != 0)
                {
                    moves.push_back(Coordinates(x - x_offset, y + y_offset));
                }
            }
        }

        return moves;
    }
}