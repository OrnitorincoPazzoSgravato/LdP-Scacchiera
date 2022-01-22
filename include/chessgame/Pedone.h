/*

    @author: Barbato Federico
    @date: 2021-12-27

*/

#ifndef PEDONE_H
#define PEDONE_H

#include <vector>

#include "Piece.h"
#include "Chessboard.h"

namespace chessgame
{

    /*

        this class represents a pedone of the game.

    */
    class Pedone : public Piece
    {

    public:
        bool has_already_moved;
        Pedone() = delete;
        Pedone(PieceColor color, const char symbol) : has_already_moved{false}, Piece(color, symbol) {}
        vector<Coordinates> getMoves(const Chessboard &board, const Coordinates &coord) override;
    };

}

#endif // PEDONE_H