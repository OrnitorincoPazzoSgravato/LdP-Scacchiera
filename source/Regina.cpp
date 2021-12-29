/*

    @author: Barbato Federico
    @date: 2021-12-27

*/
#include "../include/Regina.h"

namespace chessgame
{

    Regina::Regina(PieceColor color, const char symbol) : Piece(color, symbol)
    {
    }

    Regina::Regina() : Piece()
    {
    }

    /*

        This method returns the possible moves of the piece.
        Offsets are used to set the possible moves of the piece
        and they are calculated for each direction of the current piece.

        @arg: const vector<vector<Piece>>&  chessboard of the game
        @arg: const Coordinates &coord coordinates of the current piece

        @return: vector<Coordinates> of the possible moves of the current piece

    */
    vector<Coordinates> Regina::getMoves(Chessboard *board, const Coordinates &coord)
    {
        vector<Coordinates> moves;

        // Vertical up check
        this->verticalFinder(board, coord, moves, 1);

        // Vertical down check
        this->verticalFinder(board, coord, moves, -1);

        // Horizontal left check
        this->horizontalFinder(board, coord, moves, -1);

        // Horizontal right check
        this->horizontalFinder(board, coord, moves, 1);

        // Diagonal up right check
        this->diagonalFinder(board, coord, moves, 1, 1);

        // Diagonal down right check
        this->diagonalFinder(board, coord, moves, 1, -1);

        // Diagonal up left check
        this->diagonalFinder(board, coord, moves, -1, 1);

        // Diagonal down left check
        this->diagonalFinder(board, coord, moves, -1, -1);

        return moves;
    }

    void Regina::horizontalFinder(Chessboard *board, const Coordinates &coord, vector<Coordinates> &moves, int versor)
    {
        int x = coord.x;
        int y = coord.y;
        int x_offset = 0;
        int y_offset = 0;
        while (x + x_offset >= 0 && x + x_offset < 8)
        {
            if (board->get_piece(Coordinates(x + x_offset, y + y_offset)) == nullptr)
            {
                moves.push_back(Coordinates(x + x_offset, y + y_offset));
            }
            else if (board->get_piece(Coordinates(x + x_offset, y + y_offset))->getColor() != this->color)
            {
                moves.push_back(Coordinates(x + x_offset, y + y_offset));
                break;
            }
            else
            {
                break;
            }

            x_offset += versor;
        }
    }

    void Regina::verticalFinder(Chessboard *board, const Coordinates &coord, vector<Coordinates> &moves, int versor)
    {
        int x = coord.x;
        int y = coord.y;
        int x_offset = 0;
        int y_offset = 0;
        while (y + y_offset >= 0 && y + y_offset < 8)
        {
            if (board->get_piece(Coordinates(x + x_offset, y + y_offset)) == nullptr)
            {
                moves.push_back(Coordinates(x + x_offset, y + y_offset));
            }
            else if (board->get_piece(Coordinates(x + x_offset, y + y_offset))->getColor() != this->color)
            {
                moves.push_back(Coordinates(x + x_offset, y + y_offset));
                break;
            }
            else
            {
                break;
            }

            y_offset += versor;
        }
    }

    void Regina::diagonalFinder(Chessboard *board, const Coordinates &coord, vector<Coordinates> &moves, int h_versor, int v_versor)
    {
        int x = coord.x;
        int y = coord.y;
        int x_offset = 0;
        int y_offset = 0;
        while (x + x_offset >= 0 && x + x_offset < 8 && y + y_offset >= 0 && y + y_offset < 8)
        {
            if (board->get_piece(Coordinates(x + x_offset, y + y_offset)) == nullptr)
            {
                moves.push_back(Coordinates(x + x_offset, y + y_offset));
            }
            else if (board->get_piece(Coordinates(x + x_offset, y + y_offset))->getColor() != this->color)
            {
                moves.push_back(Coordinates(x + x_offset, y + y_offset));
                break;
            }
            else
            {
                break;
            }

            x_offset += h_versor;
            y_offset += v_versor;
        }
    }
}