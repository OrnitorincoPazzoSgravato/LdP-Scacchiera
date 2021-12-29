/*

    @author: Cavinato Enrico
    @date: 2021-12-30

    This abstract class represents a player.

*/

#ifndef PLAYER_H
#define PLAYER_H

#include "Utilities.h"
#include <array>



namespace chessgame
{
    class Player
    {
    protected:
        PieceColor pc;
        Player();
    public:
        virtual std::array<Coordinates,2> think() = 0;
    };
    
}

#endif