/**
 * @file Player.cpp
 * @author Riccardo Zuech
 * @brief 
 * @version 0.1
 * @date 2022-01-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "../include/Player.h";

#include "../include/Piece.h";
#include "../include/Utilities.h";

namespace chessgame {
    Piece* Player::getPromotionTarget() {
        // array that stores the allowed target promotion symbols
        std::array<char, 4> allowed_symbols;
        if(this->pieceColor == PieceColor::BLACK) {
            allowed_symbols = {'T', 'C', 'A', 'D'};
        } else {
            allowed_symbols = {'t', 'c', 'a', 'd'};
        }
        // used later to promote to the correct derived class of Piece
        int target_index;
        bool correct_symbol_entered = false;
        do {
            char target_symbol;
            std::cout << "Please, insert your desired promotion target's symbol (CASE SENSITIVE): ";
            std::cin >> target_symbol;

            // checks if allowed target of promotion
            for(int i = 0; i < 4 && !correct_symbol_entered; i++) {
                if(allowed_symbols[i] == target_symbol) {
                    target_index = i;
                    correct_symbol_entered = true;
                }
            }
        } while(!correct_symbol_entered);
        // switch statement used to return the choosen derived class of Piece
        switch(target_index) {
            case 0:
                return &Torre(this->pieceColor, allowed_symbols[target_index]);
            case 1:
                return &Cavallo(this->pieceColor, allowed_symbols[target_index]);
            case 2:
                return &Alfiere(this->pieceColor, allowed_symbols[target_index]);
            case 3:
                return &Regina(this->pieceColor, allowed_symbols[target_index]);
            default:
                return nullptr; // defaults to nullptr for error-checking
        }
    }
}