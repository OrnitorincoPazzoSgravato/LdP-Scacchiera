/*

    @author: Barbato Federico
    @date: 2021-12-27

*/

#ifndef RE_H
#define RE_H

#include <vector>

#include "Piece.h"

namespace chessgame
{

    /*

        this class represents a pedone of the game.

    */
    class Re : public Piece
    {

    public:
        Re();
        Re(PieceColor color, const char symbol);
        vector<Coordinates> getMoves(vector<vector<Piece *>> &board, const Coordinates &coord) override;
    };

}

#endif // RE_H