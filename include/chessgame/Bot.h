/**
 * @file Bot.h
 * @author Enrico Cavinato
 * @brief This class implement a Bot
 * @version 0.1
 * @date 2022-01-10
 * 
 * @copyright Copyright (c) 2022
 * 
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
     * @note when an istance of Bot thinks, it starts considering pieces from a certain pseudo-randomic point and for each piece it tryes all its possible moves, starting from
     * a randomic point in the sequence. The method to reset the starting point of think must be called after a valid move has been returned, in order to mantain
     * this pseduo-randomic behaviour.
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
        /**
         * @brief Function used to reset the internal starting point for moves generation.
         * 
         */
        void resetBotSeed() {
            // pseudo-random (half of the time it's a random starting point, the other half it goes to the next cell)
            // this prevents a piece from going back and forth most of the time while keeping a mostly randomic behaviour
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
        /**
         * @brief index of the last used move
         * 
         */
        int last_move_index;
        /**
         * @brief number of moves tied of the currently analyzed piece. It is a negative number when it must be re-calculated
         * 
         */
        int moves_used;
        /**
         * @brief starting point for searching pieces
         * 
         */
        Coordinates starting_tile;
        /**
         * @brief Default constructor Disabled
         * 
         */
        Bot() = delete;
    };
}

#endif