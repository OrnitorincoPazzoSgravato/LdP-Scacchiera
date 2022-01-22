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
#include <stdexcept>

#include "../../include/chessgame/Chessboard.h"

namespace chessgame
{

    Coordinates::Coordinates(int x_coord, int y_coord) : x{x_coord}, y{y_coord}
    {
        if(x == -1 && y == -1) {
            this->symbol = "XX";
        }
        else if((x < 0 && x >= chessgame::COLUMNS) || (y < 0 && y >= chessgame::ROWS)) {
            throw std::invalid_argument("Coordinates out of bounds");
        }
        else {
            char col = x + 'A';
            char row = y + '1';
            this->symbol = std::string() + col + row;
        }
    }

    Coordinates::Coordinates(std::string symbol)
    {
        this->symbol = symbol;

        char col = symbol[0];
        char row = symbol[1];

        if((col == 'x' || col == 'X') && (row == 'x' || row == 'X')) {
            this->symbol = "XX";
            this->y = -1;
            this->x = -1;
            return;
        }
        
        if (row >= '9' || row <= '0')
            throw std::invalid_argument("Row out of bounds.");
        else 
            this->y = (row - '0') - 1;
        
        if(col >= 'a' && col <= 'h')
            this->x = (col - 'a');
        else if(col >= 'A' && col <= 'H')
            this->x = (col - 'A');
        else
            throw std::invalid_argument("Column out of bounds.");
    }
}