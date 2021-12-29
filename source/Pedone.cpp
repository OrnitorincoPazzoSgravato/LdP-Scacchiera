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

    /*
        This method returns the possible moves of the piece.
        The y_offset is used to set if the movement is up or down according to the color of the piece
        while the x_offset is used only for the diagonal movements independently of the color of the piece.

        @arg: const vector<vector<Piece>>&  chessboard of the game
        @arg:const Coordinates &coord coordinates of the current piece

        @return: vector<Coordinates> of the possible moves of the current piece

    */
    vector<Coordinates> Pedone::getMoves(Chessboard *board, const Coordinates &coord)
    {
        vector<Coordinates> moves;

        int x = coord.x;
        int y = coord.y;

        int y_offset = 0;
        int x_offset = 0;

        if (this->color == PieceColor::WHITE)
        {
            y_offset = 1;
        }
        else
        {
            y_offset = -1;
        }

        // Control if the y move is inside the board
        if (y + y_offset >= 0 && y + y_offset < 8)
        {
            // Control if the end position is empty (only vertical movement)
            if (board->get_piece(Coordinates(x + x_offset, y + y_offset)) == nullptr)
            {
                moves.push_back(Coordinates(x, y + y_offset));
            }

            x_offset = 1;

            // Control if the x move is inside the board (right diagonal movement)
            if (x + x_offset >= 0 && x + x_offset < 8)
            {

                // Control if the end position is an enemy (only diagonal movement)

                if (board->get_piece(Coordinates(x + x_offset, y + y_offset))->getColor() != this->color && board->get_piece(Coordinates(x + x_offset, y + y_offset)) != nullptr)
                {
                    moves.push_back(Coordinates(x + x_offset, y + y_offset));
                }
            }

            // Control if the x move is inside the board (left diagonal movement)
            if (x - 1 >= 0 && x - 1 < 8)
            {

                // Control if the end position is an enemy (only diagonal movement)

                if (board->get_piece(Coordinates(x + x_offset, y + y_offset))->getColor() != this->color && board->get_piece(Coordinates(x + x_offset, y + y_offset)) != nullptr)
                {
                    moves.push_back(Coordinates(x - 1, y + y_offset));
                }
            }
        }

        return moves;
    }
}