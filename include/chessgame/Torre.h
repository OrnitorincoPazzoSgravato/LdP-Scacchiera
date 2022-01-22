/*

    @author: Barbato Federico
    @date: 2021-12-27

*/

#ifndef TORRE_H
#define TORRE_H

#include <vector>

#include "Piece.h"
#include "Chessboard.h"

namespace chessgame
{

    /*

        this class represents a pedone of the game.

    */
    class Torre : public Piece
    {

    public:
        bool has_already_moved;
        Torre() = delete;
        Torre(PieceColor color, const char symbol) : has_already_moved{false}, Piece(color, symbol) {}
        vector<Coordinates> getMoves(const Chessboard &board, const Coordinates &coord) override;

    private:
        void finder(const Chessboard &board, const Coordinates &coord, vector<Coordinates> &moves, int h_versor, int v_versor);
    };

}

#endif // TORRE_H