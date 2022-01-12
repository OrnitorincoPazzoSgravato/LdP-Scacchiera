/*

    @author: Barbato Federico
    @date: 2021-12-27

    This abstract class represents a piece of the game.

*/

#ifndef PIECE_H
#define PIECE_H

#include <vector>

//#include "Chessboard.h"
#include "Utilities.h"

namespace chessgame
{
    using std::vector;

    class Chessboard;
    class Piece
    {
        PieceColor color;
        char symbol;

    protected:
        Piece() = delete;
        Piece(PieceColor color, char symbol);

    public:
        char getSymbol();
        PieceColor getColor();
        virtual vector<Coordinates> getMoves(Chessboard &board, const Coordinates &coord) = 0;
    };
}

#endif