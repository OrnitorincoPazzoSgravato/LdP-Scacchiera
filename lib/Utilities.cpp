#include "../include/Utilities.h"

namespace chessgame
{
    Coordinates::Coordinates(int x, int y)
    {
        this->x = x;
        this->y = y;

        char col = x + 'A';
        char row = y + '1';

        this->symbol = col + row;
    }
}