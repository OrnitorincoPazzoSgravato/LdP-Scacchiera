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
#include <ostream>

#include "./chessgame/Chessboard.h"
#include "./chessgame/Utilities.h"

namespace replay_game
{
        /**
         * @brief This class implement a replay from a log file.
         *
         * Each line of log file must contain, in this order and separater with " "
         *
         *      - Initial coordinates of a valid move in symbol form, ex. "A1" coordinates of a valid move in symbol form, ex. "A1"
         *      - Final coordinate of a valid move in symbol form, ex. "A1"
         *      - Flag char for promotion : it has to be the symbol of the promoted piece after the promotion
         */
        class Replay
        {
        public:
                /**
                 * @brief Construct a new Replay object
                 *
                 * @param input a string with the input file
                 * @param output file where we print output,if it is "screen" print on screen
                 */
                Replay(const std::string &input, const std::string &output);
                /**
                 * @brief print content of input file
                 *
                 */
                void print();
                /**
                 * @brief Copy constructor disabled
                 *
                 */
                Replay(const Replay &) = delete;
                /**
                 * @brief Destroy the Replay object
                 *
                 */
                ~Replay();

        private:
                /**
                 * @brief a Chessboard where we replay the game
                 */
                chessgame::Chessboard board;
                /**
                 * @brief the input file
                 *
                 */
                std::fstream input_file;
                /**
                 * @brief the output file
                 *
                 */
                std::fstream output_file;
                /**
                 * @brief is this a onscreen replay?
                 *
                 */
                bool is_onscreen_replay{false};
                /**
                 * @brief make the move in a chessboard
                 *
                 */
                std::array<chessgame::Coordinates, 2> move();
                /**
                 * @brief this function checks if this move is an arrocco and move the other piece ( tower or king)
                 *
                 * @param from initial cell of the move
                 * @param to final cell of the move
                 */
                void arrocco_move(const chessgame::Coordinates from, const chessgame::Coordinates to);
                /**
                 * @brief check if the move is an enpassant capture and capture the opposite paw
                 *
                 * @param from initial cell of the move
                 * @param to final cell of the move
                 */
                void en_passant_capture(const chessgame::Coordinates &from, const chessgame::Coordinates &to);
                /**
                 * @brief print on file
                 *
                 */
                void print_on_file();
                /**
                 * @brief print on screen
                 *
                 */
                void print_on_screen();
        };
        /**
         * @brief Coordinate iniziali torre destra nera H8
         */
        const chessgame::Coordinates T_destra{"H8"};
        /**
         * @brief Coordinate iniziali torre sinistra nera A8
         */
        const chessgame::Coordinates T_sinistra{"A8"};
        /**
         * @brief Coordinate iniziali torre destra bianca H1
         */
        const chessgame::Coordinates t_destra{"H1"};
        /**
         * @brief Coordinate iniziali torre sinistra bianca A1
         */
        const chessgame::Coordinates t_sinistra{"A1"};
        /**
         * @brief Coordinate iniziali RE NERO E8
         */
        const chessgame::Coordinates Re_nero_init{"E8"};
        /**
         * @brief Coordinate iniziali RE BIANCO E1
         */
        const chessgame::Coordinates re_bianco_init{"E1"};
}

#endif