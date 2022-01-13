// ho aggiunto gli operatori di confronto (RIccardo)

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
        bool operator==(const Coordinates &other_coord) const
        {
            return this->x == other_coord.x && this->y == other_coord.y;
        }
        bool operator!=(const Coordinates &other__coord) const
        {
            return !(*this == other__coord);
        }
    };
}

#endif