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
    class Player
    {
    protected:
        PieceColor pieceColor;
        Player() = delete;

    public:
        /**
         * @brief Construct a new Player object
         *
         * @param p_color the color of the Pieces this player controls
         */
        Player(const PieceColor p_color)
            : pieceColor(p_color)
        {
        }

        /**
         * @brief The act of thinking
         *
         * @return std::array<Coordinates, 2> an array that cointains the coordinates of the move
         */
        virtual std::array<Coordinates, 2> think() = 0;

        /**
         * @brief Get the Promotion Target object
         *
         * @return Piece* a pointer to the target
         */

        virtual char getPromotionTarget() = 0;
        /**
         * @brief Get the Color object
         *
         * @return PieceColor the color of this player
         */

        PieceColor getColor()
        {
            return this->pieceColor;
        }
    };
}

#endif