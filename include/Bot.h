/*

    @author: Cavinato Enrico
    @date: 2021-12-30

    This class represents a bot.

*/

#ifndef BOT_H
#define BOT_H

#include "Utilities.h"
#include <array>
#include "Player.h"



namespace chessgame
{
    class Bot : Player
    {
    public:
        Bot(const PieceColor&);
        std::array<Coordinates,2> think();
    };
    
}

#endif