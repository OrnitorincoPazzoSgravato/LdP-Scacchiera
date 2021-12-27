#ifndef UTILITIES_H
#define UTILITIES_H

#include <stdlib.h>
namespace chessgame
{
    class PieceColor
    {
    public:
        enum Color
        {
            WHITE,
            BLACK
        };
    };

    class Coordinates
    {
    public:
        Coordinates(int x, int y);
        Coordinates();
        int x;
        int y;
    };
}

#endif