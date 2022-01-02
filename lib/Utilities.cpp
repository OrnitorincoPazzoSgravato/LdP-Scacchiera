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

    Coordinates::Coordinates(string symbol)
    {
        this->symbol = symbol;

        char col = symbol[0];
        char row = symbol[1];

        this->x = col - 'A';
        this->y = row - '1';
    }
}