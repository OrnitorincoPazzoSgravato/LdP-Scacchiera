/*

    @author: Cavinato Enrico
    @date: 2021-12-30

    This class represents a human player.

*/

#ifndef HUMAN_H
#define HUMAN_H

#include "Utilities.h"
#include <array>
#include "Player.h"



namespace chessgame
{
    class Human : Player
    {
    public:
        Human(const PieceColor&);
        std::array<Coordinates,2> think();
    };
    
}

#endif