/*

    @author: Enrico Cavinato
    @date: 2021-12-29

*/

#include "../include/Player.h"

namespace chessgame
{
    using std::array;

    Player::Player(const PieceColor& p) 
        :pc{p}
    {}
    array<Coordinates,2> Player::think()
    {
        string from,to;
        std::cin >> from >> to;
        return array<Coordinates,2> {Coordinates(from),Coordinates(to)};
    }
}