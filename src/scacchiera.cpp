/**
 * @file scacchiera.cpp
 * @author Riccardo Zuech
 * @brief 
 * @version 0.1
 * @date 2022-01-14
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <iostream>
#include "../include/Game.h"

int main(int argc, char** argv) {
    if(argc != 2) return 0;
    char p1 = argv[1][0];
    char p2 = argv[1][1];
    bool is_bot_game = false;
    if(!(p1 == 'p' || p1 == 'c') || p2 != 'c') {
        std::cout << "Invalid argument. Pleasy use 'pc' or 'cc'.";
        return 0;
    }
    else if(p1 == 'c') is_bot_game = true;
    gameplay::Game game {is_bot_game};
    game.play();
    return 0;
}