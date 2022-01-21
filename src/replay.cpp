/**
 * @file replay.cpp
 * @author Enrico Cavinato
 * @brief 
 * @version 0.1
 * @date 2022-01-17
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <iostream>
#include <string>

#include "../include/Replay.h"

int main(int argc,char** argv) {
    // if screen print
    if (argc < 3 || argc >4)
        throw std::invalid_argument("Invalid number of argumensts");
    if(argc == 3)
    {
        replay_game::Replay replay {argv[2]};
        replay.print();
    }
    // else file print
    else if(argc == 4)
    {
        replay_game::Replay replay {argv[2],argv[3]};
        replay.print();
    }
    return 0;
}
