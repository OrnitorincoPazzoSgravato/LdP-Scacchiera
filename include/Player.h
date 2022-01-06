/*

    @author: Cavinato Enrico
    @date: 2021-12-30

    This abstract class represents a player.

*/

#ifndef PLAYER_H
#define PLAYER_H

#include "./Utilities.h"
#include <array>
#include <iostream>

namespace chessgame
{
    class Player {
        public:
            PieceColor pc;
            Player();
            Player(const PieceColor& p_color)
                :pc(p_color)
            {}
            /*

            @brief: This function represents the act of thinking a move

            @return: array<Coordinates,2> the original and final coordinates of the piece we want to move
            */

            std::array<Coordinates,2>& think()
            {
                string from,to;
                std::cin >> from >> to;
                return std::array<Coordinates,2> {Coordinates(from),Coordinates(to)};
            }
    };
}

#endif