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
#include <string>
#include <fstream>
#include <exception>

#include "./chessgame/Chessboard.h"
#include "./chessgame/Utilities.h"

namespace replay_game
{
        /**
         * @brief This class implement a replay from a log file.
         *
         * Each line of log file must contain, in this order and separater with " "
         *
         *      - @Initial coordinates of a valid move in string form, ex. "A1"\n
         *      - Final coordinate of a valid move in symbol form, ex. "A1"
         *      - Flag char for promotion : it has to be the symbol of the promoted piece after the promotion
         *      - Flag char for check : * if not check, 0 if white in check, 1 if black on check
         *      - Flag int for end of game: 0 if game did not end, 1 if game is a draw, 2 if white won, 3 if black won
         */
        class Replay
        {
        public:
                /**
                 * @brief Construct a new Replay object: this istance will operate a print on file
                 *
                 * @param input a string with the name of input file
                 * @param output a string with the name oft output file
                 */
                Replay(const std::string &input, const std::string &output)
                    : is_onscreen_replay{false}, inputstring{input}, outputstring{output}
                {
                }
                /**
                 * @brief Construct a new Replay object, this istance will operate a print on screen
                 *
                 * @param input a string with the input file
                 */
                Replay(const std::string &input)
                    : is_onscreen_replay{true}, inputstring{input}
                {
                }
                /**
                 * @brief print content of input file
                 *
                 * @throw std::invalid_argument if input file does not exist or cannot be open
                 * @throw std::invalid_argument if output file does not exist or cannot be open
                 *
                 */
                void print();
                /**
                 * @brief Copy constructor disabled
                 *
                 */
                Replay(const Replay &) = delete;
                /**
                 * @brief Destroy the Replay object, release resources
                 *
                 */
                ~Replay();

        private:
                /*-----------------MEMBER VARIABLES-------------------*/
                /**
                 * @brief a Chessboard where we replay the game
                 */
                chessgame::Chessboard board;
                /**
                 * @brief input and output stream
                 *
                 */
                std::fstream input_file, output_file;
                /**
                 * @brief strings with input and output file name
                 *
                 */
                std::string inputstring, outputstring;
                /**
                 * @brief is this a onscreen replay?
                 *
                 */
                bool is_onscreen_replay;

                /*-----------------PRIVATE MEMBER FUNCTIONS-------------------*/
                /**
                 * @brief make the move in the replay chessboard
                 *
                 * @return std::array<chessgame::Coordinates, 2> an array with coordinates of the move
                 * 
                 * @throw std::invalid_argument if the initial cell is empty 
                 *
                 */
                std::array<chessgame::Coordinates, 2> move();
                /**
                 * @brief Check if this move is an arrocco and move the other piece (tower or king)
                 *
                 * @param from initial cell of the move
                 * @param to final cell of the move
                 */
                void arrocco_move(const chessgame::Coordinates &from, const chessgame::Coordinates &to);
                /**
                 * @brief check if the move is an enpassant capture and capture the opponent's paw
                 *
                 * @param from initial cell of the move
                 * @param to final cell of the move
                 */
                void en_passant_capture(const chessgame::Coordinates &from, const chessgame::Coordinates &to);
                /**
                 * @brief print on file output_file a replay of the game in input_file
                 *
                 */
                void print_on_file();
                /**
                 * @brief print on screen a replay of the game in input_file
                 *
                 */
                void print_on_screen();
        };

        /*------------------HELPER FUNCTIONS AND CONSTANTS-----------------*/

        /**
         * @brief Initial coordinates of towers for arrocco
         */
        const chessgame::Coordinates T_destra{"H8"}, T_sinistra{"A8"}, t_destra{"H1"}, t_sinistra{"A1"};
        /**
         * @brief Initial coordinates of kings for arrocco
         */
        const chessgame::Coordinates Re_nero_init{"E8"}, re_bianco_init{"E1"};

        /**
         * @brief helper function. Check if input is valid and returns a string to print
         *
         * @param check_flag must be '*' if a check did not occur, '0' if white is in check, '1' if black is in check
         *
         * @return std::string to warn which player is in  check, "" if a check did not occur
         *
         * @throw std::invalid_argument if input is not {*,0,1}
         */
        std::string kingcheck_string(char check_flag);
        /**
         * @brief helper function. Check if coordinates are in right layout
         *
         * @param initial coordinate from symbol
         * @param final coordinate to symbol
         *
         * @throw std::invalid_argument if Coordinates are in wrong layout or invalid
         */
        void check_input_from_file(const std::string &initial, const std::string &final);
        /**
         * @brief helper function. Check if game ended
         *
         * @param i flag char: 0 if game not ended, 1 if game is a draw, 2 if black won, 3 if white won
         * @return std::string  if game did not end return "" else if game ended return a string to print
         *
         * @throw std::invalid_argument if input is not {0,1,2,3}
         */
        std::string end_of_game_check(int i);
}

#endif