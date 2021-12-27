#ifndef UTILITIES_H
#define UTILITIES_H

#include <stdlib.h>
#include <string>

namespace chessgame
{
    using std::string;

    enum PieceColor
    {
        WHITE,
        BLACK
    };

    class Coordinates
    {
    public:
        int x;
        int y;
        string symbol;

        Coordinates(int x, int y);
        Coordinates();
    };
}

#endif