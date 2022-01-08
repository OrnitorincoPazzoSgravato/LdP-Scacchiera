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
    // note: no need to redefine the public interface of Player, just the methods to be overridden (and the constructor)
    class Bot : public Player {
        
        public:
            /**
             * @brief Calls the constructor of the superclass Player, additional operations TBD
             * 
             */
            Bot();
            /**
             * @brief Calls the constructor of the superclass Player, assigning the specified player color.
             * Additional operations TBD
             * 
             */
            Bot(const PieceColor& p_color);
            /**
            * 
            *@brief: This function represents the act of thinking a move. Overloads the function Player::think() and randomize it
            *
            *@param: the chessboard of the game this bot belongs to
            *
            *@return: array<Coordinates,2> the original and final coordinates of the piece we want to move
            */
            std::array<Coordinates,2>& think(Chessboard&);
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