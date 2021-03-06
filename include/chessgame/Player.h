/**
 * @file Player.h
 * @author Enrico Cavinato
 * @brief This abstact class represent a player, human or bot
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
    /**
     * @brief coordinates for castling
     * 
     */
    static const Coordinates black_castling_toleft{"C8"},black_castling_toright{"G8"};
    static const Coordinates white_castling_toleft{"C1"},white_castling_toright{"G1"};
    
    class Player
    {
    protected:
        /**
         * @brief Color of this player
         * 
         */
        PieceColor pieceColor;
        /**
         * @brief Default constructor disabled
         * 
         */
        Player() = delete;

    public:
        /**
         * @brief state if this is a human or bot player
         * 
         */
        bool is_human;
        /**
         * @brief Construct a new Player object
         *
         * @param p_color the color of the Pieces this player controls
         */
        Player(const PieceColor p_color, bool human)
            : pieceColor(p_color), is_human{human}
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