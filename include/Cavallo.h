/*

    @author: Barbato Federico
    @date: 2021-12-27

*/

#ifndef CAVALLO_H
#define CAVALLO_H

#include <vector>

#include "Piece.h"

namespace chessgame
{

    /*

        this class represents a pedone of the game.

    */
    class Cavallo : public Piece
    {

    public:
        Cavallo();
        Cavallo(PieceColor color, const char symbol);
        vector<Coordinates> getMoves(vector<vector<Piece *>> &board, int x, int y) override;
    };

}

#endif // CAVALLO_H