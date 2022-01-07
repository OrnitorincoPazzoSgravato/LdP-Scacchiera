/**
 * @file Replay.h
 * @author Enrico Cavinato
 * @brief 
 * @version 0.1
 * @date 2022-12-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef REPLAY_H
#define REPLAY_H

#include <iostream>
#include <istream>
#include <string>

#include "Chessboard.h"


namespace chessgame 
{
    /**
	 * @brief Class that implements the replay of a game from a log file
	 */
    class Replay
    {
        Chessboard cboard;    
    public:
        Replay();
        void print_onscreen(const std::string&);
        void print_on_file(const std::string& ,const std::string&);
    };
}


#endif