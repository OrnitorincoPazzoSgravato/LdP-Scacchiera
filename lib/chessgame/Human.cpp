/**
 * @file Human.cpp
 * @author Riccardo Zuech
 * @brief Definition of methods of Human
 * @version 0.1
 * @date 2022-01-12
 *
 * @copyright Copyright (c) 2022
 *
 */


#include "../../include/chessgame/Human.h"

#include "../../include/chessgame/Chessboard.h"

namespace chessgame
{
    char Human::getPromotionTarget()
    {
        // array that stores the allowed target promotion symbols
        std::array<char, 4> allowed_symbols;
        if (this->pieceColor == chessgame::BLACK)
            allowed_symbols = {chessgame::BLACK_TOWER, chessgame::BLACK_HORSE, chessgame::BLACK_BISHOP, chessgame::BLACK_QUEEN};
        else
            allowed_symbols = {chessgame::WHITE_TOWER, chessgame::WHITE_HORSE, chessgame::WHITE_BISHOP, chessgame::WHITE_QUEEN};

        // used later to promote to the correct derived class of Piece
        int target_index;
        bool correct_symbol_entered = false;
        do
        {
            char target_symbol;
            std::cout << "Please, insert your desired promotion target's symbol (CASE SENSITIVE): ";
            std::cin >> target_symbol;

            // checks if allowed target of promotion
            for (int i = 0; i < 4 && !correct_symbol_entered; i++)
            {
                if (allowed_symbols[i] == target_symbol)
                {
                    target_index = i;
                    correct_symbol_entered = true;
                }
            }
        } while (!correct_symbol_entered);
        return allowed_symbols[target_index];
    }

    
    bool check_move(const std::array<std::string, 2> &move)
    {
        for (int i = 0; i < 2; i++) // checking if the move's coordinates are out of the chessboard coordinates' bounds
        {
            try {
                chessgame::Coordinates {move[i]};
            }
            catch(std::invalid_argument) {
                return false;
            }
        }
        return true;
    }
}