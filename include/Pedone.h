/*

    @author: Barbato Federico
    @date: 2021-12-27

*/

#ifndef PEDONE_H
#define PEDONE_H

#include <vector>

#include "Piece.h"

namespace chessgame
{

    /*

        this class represents a pedone of the game.

    */
    class Pedone : public Piece
    {
    private:
        bool is_already_moved;

    public:
        Pedone();
        Pedone(PieceColor color, const char symbol);
        vector<Coordinates> getMoves(Chessboard &board, const Coordinates &coord) override;
    };

}

#endif // PEDONE_H