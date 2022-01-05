/*

    @author: Cavinato Enrico
    @date: 2021-12-30

    This abstract class represents a player.

*/

#ifndef PLAYER_H
#define PLAYER_H

#include "Utilities.h"
#include <array>
#include <iostream>



namespace chessgame
{
    class Player {
        PieceColor pc;
        public:
            Player();
            Player(const PieceColor&);
            std::array<Coordinates,2>& think();
    };
}

#endif