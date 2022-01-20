/**
 * @file Replay.cpp
 * @author Enrico Cavinato
 * @brief
 * @version 0.1
 * @date 2022-01-16
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <string>
#include <fstream>
#include <ostream>
#include <chrono>
#include <thread>
#include <stdexcept>
#include <iostream>
#include <istream>

#include "../include/Replay.h"
#include "../include/Game.h"
#include "../include/chessgame/Utilities.h"
#include "../include/chessgame/Chessboard.h"
#include "../include/chessgame/Human.h"

namespace replay_game
{
    const std::string gameover_string {"********************** GAME OVER **********************"};

    void Replay::print()
    {
        // open input file
        input_file.open(inputstring, std::fstream::in);

        // checks if open
        if (!input_file)
            throw std::invalid_argument("This file does not exist or not open properly");

        // if this is a onscreen replay
        if (is_onscreen_replay)
            print_on_screen();
        else
        {
            //open output file
            output_file.open(outputstring, std::fstream::out);

            // check if output file is open
            if (!output_file.is_open())
                throw std::invalid_argument("File not open");
            print_on_file();
            output_file.close();
        }
        input_file.close();
    }

    void Replay::print_on_file()
    {
        int turn{0};
        output_file << "-----------REPLAY OF THE GAME-----------\n" << std::endl;
        output_file << this->board.snapshot() << std::endl;

        // while loop
        while (!input_file.eof())
        {
            // next turn
            turn++;

            // make the move
            std::array<chessgame::Coordinates, 2> this_move = move();
            std::string from{this_move[0].symbol};
            std::string to{this_move[1].symbol};

            // print checkmate contition
            char checkmate_char;
            this->input_file >> checkmate_char;
            output_file << kingcheck_string(checkmate_char) <<std::endl;

            // print state of chessboard
            output_file << this->board.snapshot() << std::endl;

            output_file << "Moved: " << this->board.get_piece(to)->getSymbol() << " from " << from << " to " << to << std::endl;
            output_file << "********************** End of turn " << turn << " **********************" << std::endl;
        }
        output_file << gameover_string << std::endl;
    }

    void Replay::print_on_screen()
    {
        std::cout << "-----------REPLAY OF THE GAME-----------\n";
        std::cout << this->board.snapshot() << "\n";
        int turn{0};

        // while loop input
        while (!input_file.eof())
        {
            turn++;
            // wait 1 second before the move
            std::this_thread::sleep_for(std::chrono::seconds(1));

            // make the move
            std::array<chessgame::Coordinates, 2> this_move = move();
            std::string from{this_move[0].symbol};
            std::string to{this_move[1].symbol};

            // print the state of chessboard
            std::cout << this->board.snapshot() + "\n";

            // print checkmate contition
            char checkmate_flag;
            this->input_file >> checkmate_flag;
            std::cout << kingcheck_string(checkmate_flag) << "\n";

            std::cout << "Moved: " << this->board.get_piece(to)->getSymbol() << " from " << from << " to " << to << std::endl;
            std::cout << "********************** End of turn " << turn << " **********************\n";
        }
        std::cout << gameover_string;
    }

    std::array<chessgame::Coordinates, 2> Replay::move()
    {
        // elements of the move:
        std::string initial;
        std::string final;
        char promotion_char;

        // get input
        this->input_file >> initial >> final >> promotion_char;

        //chacks if input is valid
        // bool valid_formula{chessgame::check_move(std::array<std::string, 2>{initial, final})};
        //if (!valid_formula)
        //    throw std::invalid_argument("Invalid string in log file");

        chessgame::Coordinates from{initial};
        chessgame::Coordinates to{final};

        // if to is an empty cell
        if (!this->board.get_piece(to))
        {
            // if this is an enpassant or arrocco move
            if (this->board.get_piece(from)->getSymbol() == chessgame::WHITE_PAW || this->board.get_piece(from)->getSymbol() == chessgame::BLACK_PAW)
                en_passant_capture(from, to);
            arrocco_move(from, to);

            // move
            board.swap_positions(from, to);
        }
        // if to is not an empty cell
        else
        {
            board.set_piece(to, nullptr);
            board.swap_positions(from, to);
        }

        // try promotion
        this->board.promote(promotion_char, to);

        return std::array<chessgame::Coordinates, 2>{from, to};
    }

    void Replay::arrocco_move(const chessgame::Coordinates from, const chessgame::Coordinates to)
    {

        // se non è arrocco termina
        if (!gameplay::isArrocco(std::array<chessgame::Coordinates, 2>{from, to}, board))
            return;

        // se muovo il re
        if (from == Re_nero_init || from == re_bianco_init)
        {
            // case 1 : nero a sinisra
            if (to.symbol[0] < Re_nero_init.symbol[0])
                this->board.swap_positions(T_sinistra, chessgame::Coordinates{"D8"});
            // case 2 :nero a destra
            else if (to.symbol[0] > Re_nero_init.symbol[0])
                this->board.swap_positions(T_destra, chessgame::Coordinates{"F8"});

            // case 3:bianco a sinistra
            else if (to.symbol[0] < re_bianco_init.symbol[0])
                this->board.swap_positions(t_sinistra, chessgame::Coordinates{"D1"});

            // case 4 :bianco a destra
            else if (to.symbol[0] > re_bianco_init.symbol[0])
                this->board.swap_positions(chessgame::Coordinates{"F1"}, t_destra);
            return;
        }
        // case 5 : muovo la torre nera di sinistra
        else if (from == T_sinistra)
            this->board.swap_positions(Re_nero_init, chessgame::Coordinates{"C8"});

        // case 6 : muovo torre nera di destra
        else if (from == T_destra)
            this->board.swap_positions(Re_nero_init, chessgame::Coordinates{"G8"});
        // case 7 : muovo torre bianca di sinistra
        else if (from == t_sinistra)
            this->board.swap_positions(re_bianco_init, chessgame::Coordinates{"C1"});

        // case 8 :muovo torre bianca di destra
        else if (from == t_destra)
            this->board.swap_positions(re_bianco_init, chessgame::Coordinates{"G1"});
    }

    void Replay::en_passant_capture(const chessgame::Coordinates &from, const chessgame::Coordinates &to)
    {
        // if column is different but cell is empty
        bool different_column{from.x != to.x};
        bool destination_empty{!(from.x != to.x)};
        if (different_column && destination_empty)
        {
            chessgame::Coordinates enpassant_coord{to.x, from.y};
            this->board.set_piece(enpassant_coord, nullptr);
        }
    }

    Replay::~Replay()
    {
        // close fstreams
        if (this->input_file.is_open())
            this->input_file.close();
        if (this->output_file.is_open())
            this->output_file.close();
    }

    std::string kingcheck_string(char checkmate_flag)
    {
        switch (checkmate_flag)
            {
            case '0':
                return "White player is in check";
                break;
            case '1':
                return "Black player is in check";
                break;
            default:
                return "";
            }
    }
}