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
         * @brief print a game on screen from a log file. The function prints the seuqence of the states of the chessboard before and avter every move
         * 
         * @param input_file the log file we want to read
         * 
         */
        void print_onscreen(const std::string &input_file);
        /**
         * @brief print a game on a log file from a log file. The function prints the seuqence of the states of the chessboard before and avter every move
         * 
         * @param input_file the log file we want to read
         * 
         */
        void print_on_file(const std::string &input_file, const std::string &output_file);
}

#endif