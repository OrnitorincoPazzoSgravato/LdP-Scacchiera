/*

    @author: Barbato Federico
    @date: 2021-12-27

*/

#ifndef REGINA_H
#define REGINA_H

#include <vector>

#include "Piece.h"
#include "Chessboard.h"

namespace chessgame
{

    /*

        this class represents a pedone of the game.

    */
    class Regina : public Piece
    {

    public:
        Regina() = delete;
        Regina(PieceColor color, const char symbol);
        vector<Coordinates> getMoves(Chessboard &board, const Coordinates &coord) override;

    private:
        void finder(Chessboard &board, const Coordinates &coord, vector<Coordinates> &moves, int h_versor, int v_versor);
    };

}

#endif // REGINA_H