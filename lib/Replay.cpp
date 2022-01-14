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

#include <stdexcept>

#include "../include/Replay.h"

namespace chessgame
{
    void print_onscreen(const std::string& input_file)
    {
        // opens the input file
        std::ifstream ist { input_file };

        //if the name is invalid
        if (!ist) throw std::invalid_argument("This file does not exist"); 

        // create a chessboard to recreate the moves
        Chessboard board;

        // print initial configuration
        std::cout << board.snapshot();

        //while loop input
        while(!ist.eof())
        {
            Coordinates from ;
            Coordinates to ;
            // get coordinates in from
            // get Coordinates in to

            // update chessboard
            Piece* p {board.get_piece(from)};
            board.set_piece(to,p);

            // print configuration
            std::cout << board.snapshot();

        }
        ist.close();
    }
     void print_on_file(const std::string &input_file, const std::string &output_file)
     {
         // opens the input file
        std::ifstream ist { input_file };

        //if the name is invalid
        if (!ist) throw std::invalid_argument("This file does not exist"); 

        // create a chessboard to recreate the moves
        Chessboard board;

     }

}