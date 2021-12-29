/*

    @author: Barbato Federico
    @date: 2021-12-27

    This abstract class represents a piece of the game.

*/

#ifndef PIECE_H
#define PIECE_H

#include <vector>

#include "Chessboard.h"
#include "Utilities.h"

namespace chessgame
{
    using std::vector;

    class Piece
    {

    protected:
        PieceColor color;
        char symbol;

        Piece();
        Piece(PieceColor color, char symbol);

    public:
        char getSymbol() const;
        PieceColor getColor() const;
        virtual vector<Coordinates> getMoves(Chessboard *board, const Coordinates &coord) = 0;
    };
}

#endif