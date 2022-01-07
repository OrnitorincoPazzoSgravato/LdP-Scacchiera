/**
 * @file Replay.cpp
 * @author Riccardo Zuech
 * @brief 
 * @version 0.1
 * @date 2022-01-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <string>
#include <istream>

#include "stdlib.h"

#include "../include/Replay.h"

namespace chessgame
{
    void print_onscreen(std::string& input_file)
    {
        std::ifstream istr(input_file);
        if (! ist) std::runtime_error("Can't open input file");
    }
}