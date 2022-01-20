/*

    @author: Cavinato Enrico
    @date: 2021-12-30

    This class represents a bot.

*/

#ifndef BOT_H
#define BOT_H

#include "Player.h"

namespace chessgame
{
    /**
     * @brief This class represents a Bot
     *
     */
    class Bot : public Player
    {

    public:
        /**
         * @brief Calls the constructor of the superclass Player, assigning the specified player color.
         *
         *
         */
        Bot(const PieceColor &p_color, Chessboard &cboard)
            : Player{p_color}, board{cboard}, last_move_index{0}
        {
        }

        /**
         *
         *@brief This function represents the act of thinking a move. Overloads the function Player::think() and randomize it
         *
         *@return  original and final coordinates of the piece we want to move
         */
        std::array<Coordinates, 2> think();
        /**
         *
         * @brief: This method implements promotion in bot class
         *
         * @return a charachter, d or D
         *
         */
        char getPromotionTarget();

    private:
        // a reference to a chessboard in this game
        Chessboard &board;
        int last_move_index;
    };
    /**
     * @brief this helper function returns the coordinates of the cell after coord in an iteration column by column
     * WE DID NOT implemented this as a Coordinates operator++ because the iteration is
     * not a standard row by row 
     *
     * @param coord the previous coordinates
     * @return Coordinates after coord
     */
    Coordinates next_cell(const Coordinates &coord);
}

#endif