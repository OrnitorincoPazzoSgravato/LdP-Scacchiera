#include "../../include/chessgame/Utilities.h"

namespace chessgame
{
    Coordinates::Coordinates(int x, int y)
    {
        if (x < 0 || x > 7 || y < 0 || y > 7)
        {
            throw CoordinateOutOfRangeException("Coordinates Out of Range");
        }

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

        if (col - 'A' < 0 || col - 'A' > 7 || row - '1' < 0 || y > row - '1')
        {
            throw CoordinateOutOfRangeException("Coordinates Out of Range");
        }

        this->x = col - 'A';
        this->y = row - '1';
    }
}