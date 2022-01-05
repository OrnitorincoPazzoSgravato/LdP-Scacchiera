/*

    @author: Enrico Cavinato
    @date: 2021-12-29

*/

#include "../include/Bot.h"

namespace chessgame
{
    Bot::Bot() : Player() {}
    Bot::Bot(const PieceColor& p_color) : Player(p_color) {}
    /*

        This function represents the act of thinking a move
        Overloads the function Player::think() and randomize it

        @return: array<Coordinates,2> the original and final coordinates of the piece we want to move
    */
    std::array<Coordinates,2>& Bot::think() {}
}