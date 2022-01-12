/**

    @author: Barbato Federico
    @date: 2021-12-27

*/

#ifndef ALFIERE_H
#define ALFIERE_H

#include <vector>

#include "Chessboard.h"
#include "Piece.h"

namespace chessgame
{

    /*

        this class represents a pedone of the game.

    */
    class Alfiere : public Piece
    {

    public:
        Alfiere() = delete;
        Alfiere(PieceColor color, const char symbol);
        vector<Coordinates> getMoves(Chessboard &board, const Coordinates &coord) override;

    private:
        void diagonalFinder(Chessboard &board, const Coordinates &coord, vector<Coordinates> &moves, int h_versor, int v_versor);
    };

}

#endif // ALFIERE_H