/*

    @author: Enrico Cavinato
    @date: 2021-12-29

*/

#include "../include/Player.h"

namespace chessgame
{
    using std::array;
    Player::Player() {}
    Player::Player(const PieceColor& p_color) : pc{p_color} {}
        /*

        This function represents the act of thinking a move

        @return: array<Coordinates,2> the original and final coordinates of the piece we want to move
    */
    array<Coordinates,2>& Player::think()
    {
        string from,to;
        std::cin >> from >> to;
        return array<Coordinates,2> {Coordinates(from),Coordinates(to)};
    }
}