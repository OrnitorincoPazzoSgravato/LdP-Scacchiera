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
#include <fstream>

#include "../include/Replay.h"

namespace chessgame
{
    void print_onscreen(const std::string& input_file)
    {
        // opens the input file
        std::ifstream ist { input_file };
        //if the name is invalid TBD
        if (!ist) ; 

        // questa cosa inizializza ?
        Chessboard c;
        std::cout << c.snapshot();
        while(!ist.eof())
        {
            
        }



        ist.close();
    }
}