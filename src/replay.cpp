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
    if(argc == 2)
    {
        replay_game::Replay replay {argv[1]};
        replay.print();
    }
    else if(argc == 3)
    {
        replay_game::Replay replay {argv[1],argv[2]};
        replay.print();
    }
    return 0;
}
