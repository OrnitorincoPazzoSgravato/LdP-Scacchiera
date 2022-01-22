/**
 * @file Utilities.h
 * @author Riccardo Zuech
 * @brief Entities commonly used across the whole library
 * @version 0.1
 * @date 2022-01-19
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef UTILITIES_H
#define UTILITIES_H

namespace chessgame
{
    enum PieceColor
    {
        WHITE,
        BLACK
    };

    /**
     * @brief This class represent a pair of coordinates. X is the column, Y is the row.
     */
    class Coordinates
    {
    public:
        int x;
        int y;
        std::string symbol;
        /**
         * @brief Construct a new Coordinates object, initializing it to (-1, -1) as default (Invalid pair)
         * 
         */
        Coordinates() : Coordinates(-1, -1) {};
        /**
         * @brief Construct a new Coordinates object
         * 
         * @param x 
         * @param y 
         */
        Coordinates(int x, int y);
        /**
         * @brief Construct a new Coordinates object
         * 
         * @param symbol chessboard coordinates representation
         */
        Coordinates(std::string symbol);
        /**
         * @brief Construct a new Coordinates object (copy constructor)
         * 
         * @param coord 
         */
        Coordinates(const Coordinates &coord)
        {
            this->x = coord.x;
            this->y = coord.y;
            this->symbol = coord.symbol;
        }
        /**
         * @brief Assignment operator overloading
         * 
         * @param coord 
         * @return Coordinates& 
         */
        Coordinates &operator=(const Coordinates &coord)
        {
            this->x = coord.x;
            this->y = coord.y;
            this->symbol = coord.symbol;
            return *this;
        }
        /**
         * @brief "Equal to" operator overloading
         * 
         * @param other_coord 
         * @return true 
         * @return false 
         */
        bool operator==(const Coordinates &other_coord) const
        {
            return this->x == other_coord.x && this->y == other_coord.y;
        }
        /**
         * @brief "Different than" operator overloading
         * 
         * @param other_coord 
         * @return true 
         * @return false 
         */
        bool operator!=(const Coordinates &other__coord) const
        {
            return !(*this == other__coord);
        }
        // increment and decrement operators disabled
        Coordinates &operator++() = delete;
        Coordinates &operator--() = delete;
    };
}

#endif