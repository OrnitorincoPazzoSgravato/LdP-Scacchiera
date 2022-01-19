/**
 * @file Utilities.h
 * @author Riccardo Zuech
 * @brief 
 * @version 0.1
 * @date 2022-01-19
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef UTILITIES_H
#define UTILITIES_H

#include <stdlib.h>
#include <string>

#include "Exception.h"

namespace chessgame
{
    using std::string;

    enum PieceColor
    {
        WHITE,
        BLACK
    };
    /**
     * @brief This class represent a pair of coordinates
     *
     * @param x the column
     * @param y the row
     */
    class Coordinates
    {
    public:
        int x;
        int y;
        string symbol;

        Coordinates(){};
        Coordinates(int x, int y);
        Coordinates(string symbol);
        Coordinates(const Coordinates &coord)
        {
            this->x = coord.x;
            this->y = coord.y;
            this->symbol = coord.symbol;
        }
        Coordinates &operator=(const Coordinates &coord)
        {
            this->x = coord.x;
            this->y = coord.y;
            this->symbol = coord.symbol;
            return *this;
        }
        bool operator==(const Coordinates &other_coord) const
        {
            return this->x == other_coord.x && this->y == other_coord.y;
        }
        bool operator!=(const Coordinates &other__coord) const
        {
            return !(*this == other__coord);
        }
        Coordinates &operator++() = delete;
        Coordinates &operator--() = delete;
    };
}

#endif