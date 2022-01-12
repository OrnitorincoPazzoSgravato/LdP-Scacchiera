/*

    @author: Barbato Federico
    @date: 2021-12-27

*/

#ifndef RE_H
#define RE_H

#include <vector>

#include "Piece.h"
#include "Chessboard.h"

namespace chessgame
{

    /*

        this class represents a pedone of the game.

    */
    class Re : public Piece
    {

    public:
        bool has_already_moved;
        Re() = delete;
        Re(PieceColor color, const char symbol) : has_already_moved{false}, Piece(color, symbol) {}
        vector<Coordinates> getMoves(Chessboard &board, const Coordinates &coord) override;
    };

}

#endif // RE_H