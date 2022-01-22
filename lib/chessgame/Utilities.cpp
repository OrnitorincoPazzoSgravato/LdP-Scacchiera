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

#include <string>

namespace chessgame
{

    Coordinates::Coordinates(int x_coord, int y_coord) : x{x_coord}, y{y_coord}
    {

        char col = x + 'A';
        char row = y + '1';
        this->symbol = std::string() + col + row;
    }

    Coordinates::Coordinates(std::string symbol)
    {
        this->symbol = symbol;

        char col = symbol[0];
        char row = symbol[1];

        // Check if the received symbol is a column value
        if ((col <= '9' && col >= '0') && ((row <= 'Z' && row >= 'A') || (row <= 'z' && row >= 'a')))
        {
            char temp{col};
            col = row;
            row = temp;
        }
        if (col >= 'a' || col <= 'z')
        {
            col -= 'a';
        }

        this->x = col - 'A';
        this->y = row - '1';
    }
}