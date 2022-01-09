/**
 * @file Player.h
 * @author Enrico Cavinato
 * @brief 
 * @version 0.1
 * @date 2022-12-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef PLAYER_H
#define PLAYER_H

#include <array>
#include <iostream>
#include <string>

#include "./Utilities.h"
#include "./Piece.h"

namespace chessgame
{
    class Player {
        protected:
            PieceColor pieceColor;
        public:
            bool is_human;
            Player();
            /**
            *
            *@brief: Copy constructor disabled: we want players to be as unique as possible
            */
            Player(const Player&) = delete;
            Player(const PieceColor& p_color)
                :pieceColor(p_color),
                is_human(true)
            {}
            /**
            *
            *@brief: This function represents the act of thinking a move
            *   
            *@return: array<Coordinates,2> the original and final coordinates of the piece we want to move
            */

            std::array<Coordinates,2>& think()
            {
                std::string from,to;
                std::cin >> from >> to;
                return std::array<Coordinates,2> {Coordinates(from),Coordinates(to)};
            }
            Piece* getPromotionTarget();
            PieceColor getColor() {
                return this->pieceColor;
            }
    };
}

#endif