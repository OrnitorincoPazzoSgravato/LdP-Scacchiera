/*

    @author: Barbato Federico
    @date: 2021-12-27

*/

#ifndef TORRE_H
#define TORRE_H

#include <vector>

#include "Piece.h"

namespace chessgame
{

    /*

        this class represents a pedone of the game.

    */
    class Torre : public Piece
    {

    public:
        Torre();
        Torre(PieceColor color, const char symbol);
        vector<Coordinates> getMoves(Chessboard *board, const Coordinates &coord) override;

    private:
        void horizontalFinder(Chessboard *board, const Coordinates &coord, vector<Coordinates> &moves, int versor);
        void verticalFinder(Chessboard *board, const Coordinates &coord, vector<Coordinates> &moves, int versor);
    };

}

#endif // TORRE_H