/*

    @author: Barbato Federico
    @date: 2021-12-27

*/

#ifndef CAVALLO_H
#define CAVALLO_H

#include <vector>

#include "Piece.h"
#include "Chessboard.h"

namespace chessgame
{

    /*

        this class represents a pedone of the game.

    */
    class Cavallo : public Piece
    {

    public:
        Cavallo() = delete;
        Cavallo(PieceColor color, const char symbol);
        vector<Coordinates> getMoves(const Chessboard &board, const Coordinates &coord) override;
    };

}

#endif // CAVALLO_H