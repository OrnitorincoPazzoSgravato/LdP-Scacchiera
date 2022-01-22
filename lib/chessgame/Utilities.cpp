/**
 * @file Utilities.cpp
 * @author
 * @brief 
 * @version 0.1
 * @date 2022-01-19
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "../../include/chessgame/Utilities.h"

namespace chessgame
{   

    Coordinates::Coordinates(int x_coord, int y_coord) : x{x_coord}, y{y_coord}
    {
        /*if (x < 0 || x > 7 || y < 0 || y > 7)
        {
            throw CoordinateOutOfRangeException("Coordinates Out of Range");
        }*/
        char col = x + 'A';
        char row = y + '1';
        this->symbol = std::string() + col + row;
    }

    Coordinates::Coordinates(std::string symbol)
    {
        this->symbol = symbol;

        char col = symbol[0];
        char row = symbol[1];

        /*if (col - 'A' < 0 || col - 'A' > 7 || row - '1' < 0 || y > row - '1')
        {
            throw CoordinateOutOfRangeException("Coordinates Out of Range");
        }*/

        this->x = col - 'A';
        this->y = row - '1';
    }
}