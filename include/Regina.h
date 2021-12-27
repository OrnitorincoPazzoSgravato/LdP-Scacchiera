/*

    @author: Barbato Federico
    @date: 2021-12-27

*/

#ifndef REGINA_H
#define REGINA_H

#include <vector>

#include "Piece.h"

namespace chessgame
{

    /*

        this class represents a pedone of the game.

    */
    class Regina : public Piece
    {

    public:
        Regina();
        Regina(PieceColor color, const char symbol);
        vector<Coordinates> getMoves(vector<vector<Piece *>> &board, const Coordinates &coord) override;

    private:
        void horizontalFinder(vector<vector<Piece *>> &board, const Coordinates &coord, vector<Coordinates> &moves, int versor);
        void verticalFinder(vector<vector<Piece *>> &board, const Coordinates &coord, vector<Coordinates> &moves, int versor);
        void diagonalFinder(vector<vector<Piece *>> &board, const Coordinates &coord, vector<Coordinates> &moves, int h_versor, int v_versor);
    };

}

#endif // REGINA_H