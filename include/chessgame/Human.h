/**
 * @file Human.h
 * @author Enrico Cavinato
 * @brief This class implements a human player
 * @version 0.1
 * @date 2022-01-12
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef HUMAN_H
#define HUMAN_H

#include <array>
#include <string>

#include "Player.h"

namespace chessgame
{
    /**
<<<<<<< HEAD
     * @brief Helper function to check if move is valid
     * 
     * @param move array of symbols of initial and final cell of the move
     * @return true if move is valid
     * @return false if move is not valid
=======
     * @brief check if the move is valid
     *
     * @param move a move from the human player
     * @return true if valid
     * @return false if invalid
>>>>>>> c82d5c2bec114571f62d325b95cb01bfa706a73f
     */
    bool check_move(const std::array<std::string, 2> &move);

    /**
     * @brief This derived class implement a human player: the act of thinking is 
     * implemented as an input standard input
     * 
     */
    class Human : public Player
    {
    private:
        /**
         * @brief Get a move from the human player
         *
         * @param pc color of human player
         * @return std::array<std::string, 2> array with the move
         */
        std::array<std::string, 2> human_thinking()
        {
            std::string from, to;
            std::string color = this->pieceColor == chessgame::WHITE ? "white" : "black";
            std::cout << "Please state your move (" << color << "): ";
            std::cin >> from >> to;
            return std::array<std::string, 2>{from, to};
        }

    public:
        /**
         * @brief Construct a new Human object
         *
         * @param pcolor the color of this player
         */
        Human(const PieceColor pcolor)
            : Player{pcolor}
        {
        }

        /**
         * @brief This function implement the act of thinking a move by a human player
         *
         * @return std::array<Coordinates, 2> an array with a move inside the chessboard
         * @return std::array<Coordinates, 2> "XX" "XX" to print chessboard
         */
        std::array<Coordinates, 2> think()
        {
            bool valid_move{false};
            std::array<std::string, 2> move{"XX","XX"};
            while (!valid_move)
            {
                move = human_thinking();
                if (move[0] == "XX" && move[1] == "XX")
                    return std::array<Coordinates, 2>{Coordinates{"XX"}, Coordinates{"XX"}};
                valid_move = chessgame::check_move(move);
            }
            return std::array<Coordinates, 2>{Coordinates{move[0]}, Coordinates{move[1]}};
        }

        /**
         * @brief Implement the decision of the piece we want to replace the paw with
         *
         * @return Piece* a pointer to the piece we want to replace the paw with
         */
        char getPromotionTarget();
    };
}
#endif