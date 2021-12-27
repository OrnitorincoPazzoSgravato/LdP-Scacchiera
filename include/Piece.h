/*

    @author: Barbato Federico
    @date: 2021-12-27

    This abstract class represents a piece of the game.

*/

#ifndef PIECE_H
#define PIECE_H

#include <vector>

#include "Utilities.h"

namespace chessgame
{
    using std::vector;

    class Piece
    {

    protected:
        PieceColor color;
        char symbol;

    public:
        Piece();
        Piece(PieceColor color, char symbol);
        char getSymbol() const;
        PieceColor getColor() const;
        virtual vector<Coordinates> getMoves(vector<vector<Piece *>> &board, int x, int y) = 0;
    };
}

#endif