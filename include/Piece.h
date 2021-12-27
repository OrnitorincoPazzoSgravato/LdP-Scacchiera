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
        PieceColor::Color color;
        char symbol;

        Piece();
        Piece(PieceColor::Color color, char symbol);

    public:
        virtual vector<Coordinates> getMoves(const Chessboard &board);
    };
}

#endif