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
    class Bot : public Player {
        private:
        Chessboard& board;
        public:
            /**
             * @brief Calls the constructor of the superclass Player, assigning the specified player color.
             * 
             * 
             */
            Bot(const PieceColor& p_color, Chessboard& cboard)
                : Player {p_color}, board {cboard}
            {}

            /**
            * 
            *@brief This function represents the act of thinking a move. Overloads the function Player::think() and randomize it
            *
            *@return  original and final coordinates of the piece we want to move
            */
            std::array<Coordinates,2>& think();
            /** 
            *
            * @brief: This method implements promotion in bot class
            * 
            * @return: a pointer to the piece we want to replace the Pedone
            *  
            */
            Piece* getPromotionTarget();
    };
}

#endif