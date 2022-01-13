/**
 * @file Bot.cpp
 * @author Enrico Cavinato
 * @brief 
 * @version 0.1
 * @date 2022-01-13
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <array>
#include <vector>
#include <stdexcept>

#include "../../include/chessgame/Bot.h"
#include "../../include/chessgame/Chessboard.h"
#include "../../include/chessgame/Player.h"
#include "../../include/chessgame/Regina.h"

namespace chessgame
{
    std::array<Coordinates, 2> Bot::think()
    {
        std::array<Coordinates, 2> move {this->board.get_random(this->getColor())};
        return move;
    }
    char Bot::getPromotionTarget()
    {
        char c = '0';
        if (this->pieceColor == WHITE) c = 'd';
        else c = 'D';
        return c;
    }
}