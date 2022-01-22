/*

    @author: Barbato Federico
    @date: 2021-12-27

*/
#include <iostream>
#include "../../include/chessgame/Torre.h"

namespace chessgame
{

    /*

        This method returns the possible moves of the piece.
        Offsets are used to set the possible moves of the piece
        and they are calculated for each direction of the current piece.

        @arg: const vector<vector<Piece>>&  chessboard of the game
        @arg: const Coordinates &coord coordinates of the current piece

        @return: vector<Coordinates> of the possible moves of the current piece

    */
    vector<Coordinates> Torre::getMoves(const Chessboard &board, const Coordinates &coord)
    {
        vector<Coordinates> moves;

        // Vertical up check
        this->finder(board, coord, moves, 0, 1);

        // Vertical down check
        this->finder(board, coord, moves, 0, -1);

        // Horizontal left check
        this->finder(board, coord, moves, -1, 0);

        // Horizontal right check
        this->finder(board, coord, moves, 1, 0);

        return moves;
    }

    void Torre::finder(const Chessboard &board, const Coordinates &coord, vector<Coordinates> &moves, int h_versor, int v_versor)
    {
        int x = coord.x;
        int y = coord.y;
        int x_offset = h_versor;
        int y_offset = v_versor;

        // While the end cell is in the chessboard
        while (x + x_offset >= 0 && x + x_offset < COLUMNS && y + y_offset >= 0 && y + y_offset < ROWS)
        {
            // Check if the end cell is empty
            if (board.get_piece(Coordinates(x + x_offset, y + y_offset)) == nullptr)
            {
                moves.push_back(Coordinates(x + x_offset, y + y_offset));
            }
            else
            { // Else the cell is not empty

                // Check the piece color
                if (board.get_piece(Coordinates(x + x_offset, y + y_offset))->getColor() != this->getColor())
                {
                    // If the color is different, the cell is a possible move
                    moves.push_back(Coordinates(x + x_offset, y + y_offset));
                }
                // The cell is not empty so the piece can't move in the current direction
                break;
            }

            x_offset += h_versor;
            y_offset += v_versor;
        }
    }

}