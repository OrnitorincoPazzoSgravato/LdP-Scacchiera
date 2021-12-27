#ifndef UTILITIES_H
#define UTILITIES_H

#include <stdlib.h>
namespace chessgame
{
    enum PieceColor
    {
        WHITE,
        BLACK
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