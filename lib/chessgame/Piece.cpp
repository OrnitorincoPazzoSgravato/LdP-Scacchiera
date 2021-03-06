#include "../../include/chessgame/Piece.h"

namespace chessgame
{
    Piece::Piece(PieceColor color, const char symbol) : color(color), symbol(symbol) {}

    char Piece::getSymbol()
    {
        return this->symbol;
    }

    PieceColor Piece::getColor()
    {
        return this->color;
    }
}