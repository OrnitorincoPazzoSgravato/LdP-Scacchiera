/*

    @author: Cavinato Enrico
    @date: 2021-12-30

    This class represents a bot.

*/

#ifndef BOT_H
#define BOT_H

#include <array>
#include <random>

#include "Player.h"
#include "Utilities.h"
#include "Chessboard.h"

namespace chessgame
{
    
    /**
     * @brief this helper function returns the coordinates of the cell after coord in an iteration column by column
     * WE DID NOT implemented this as a Coordinates operator++ because the iteration is
     * not a standard row by row 
     *
     * @param coord the previous coordinates
     * @return Coordinates after coord
     */
    Coordinates next_cell(const Coordinates &coord);
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
            : Player{p_color, false}, board{cboard}, last_move_index{-1}, moves_used{0}, starting_tile{std::rand() % ROWS, std::rand() % COLUMNS}
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
         * @brief: This function implements promotion in bot class
         *
         * @return char of a Queen 
         *
         */
        char getPromotionTarget();

        void resetBotSeed() {
            if(std::rand() % 2 == 0) {
                starting_tile = {std::rand() % ROWS, std::rand() % COLUMNS};
            }
            else {
                starting_tile = next_cell(starting_tile);
            }
            last_move_index = -1;
            moves_used = 0;
        }

    private:
        /**
         * @brief reference to the chessboard of this game 
         */
        const Chessboard &board;
        /**
         * @brief int of the index of last move
         * 
         */
        int last_move_index;
        int moves_used;
        Coordinates starting_tile;
        Bot() = delete;
    };
}

#endif