/**
 * @file Human.h
 * @author Enrico Cavinato
 * @brief This class implements a human player
 * @version 0.1
 * @date 2022-01-12
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef HUMAN_H
#define HUMAN_H

#include <array>
#include <string>

#include "Player.h"

namespace chessgame
{
    class Human : public Player
    {
    private:
        /* data */
    public:
        /**
         * @brief Construct a new Human object
         * 
         * @param pcolor the color of this player
         */
        Human(const PieceColor pcolor) 
            : Player {pcolor}
        {}


        /**
         * @brief This function implement the act of thinking a move by a human player
         * 
         * @return std::array<Coordinates, 2> an array with the move 
         */
        std::array<Coordinates, 2> think()
        {
            std::string from, to;
            std::string color = this->pieceColor == chessgame::WHITE ? "white" : "black";
            std::cout << "Please state your move (" << color << "): ";
            std::cin >> from >> to;
            return std::array<Coordinates, 2>{Coordinates(from), Coordinates(to)};
        }

        
        /**
         * @brief Implement the decision of the piece we want to replace the paw with
         * 
         * @return Piece* a pointer to the piece we want to replace the paw with
         */
        char getPromotionTarget();        

    }; 
}
#endif