/**
 * @file Human.cpp
 * @author Riccardo Zuech
 * @brief This class represents a human player
 * @version 0.1
 * @date 2022-01-12
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "../../include/chessgame/Player.h"

#include "../../include/chessgame/Piece.h"
#include "../../include/chessgame/Utilities.h"
#include "../../include/chessgame/Torre.h"
#include "../../include/chessgame/Regina.h"
#include "../../include/chessgame/Cavallo.h"
#include "../../include/chessgame/Alfiere.h"
#include "../../include/chessgame/Human.h"

namespace chessgame
{
    char Human::getPromotionTarget()
    {
        // array that stores the allowed target promotion symbols
        std::array<char, 4> allowed_symbols;
        if (this->pieceColor == PieceColor::BLACK)
        {
            allowed_symbols = {'T', 'C', 'A', 'D'};
        }
        else
        {
            allowed_symbols = {'t', 'c', 'a', 'd'};
        }
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

    /**
     * @brief check if the move is valid
     *
     * @param move a move from the human player
     * @return true if valid
     * @return false if invalid
     */
    bool check_move(const std::array<std::string, 2> &move)
    {
        for (int i = 0; i < 2; i++)
        {
            bool uppercase{move[i][0] >= 'A' && move[i][0] <= 'H'};
            bool lowercase{move[i][0] >= 'a' && move[i][0] <= 'h'};
            bool low_or_up{uppercase || lowercase};
            bool right_length{move[i].length() == 2};
            bool right_int{move[i][1] >= 1 && move[i][1] <= 8};
            if (!low_or_up || !right_length || !right_int)
                return false;
        }
        return true;
    }
}