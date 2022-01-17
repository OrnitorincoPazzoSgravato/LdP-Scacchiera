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
#include "Game.h"

namespace replay_game
{
    Replay::Replay(const std::string &input, const std::string &output)
    {
        // open input file
        input_file.open(input, std::fstream::in);

        // if input file does not exist
        if (!input_file)
            throw std::invalid_argument("This file does not exist");

        // if file not open
        if (!input_file.is_open())
            throw std::invalid_argument("File not open");

        // it this is a screen replay
        if (output == "screen")
            is_onscreen_replay = true;
        // it this is a log file replay
        else
        {
            output_file.open(output, std::fstream::out);
            // check if output file is open
            if (!output_file.is_open())
                throw std::invalid_argument("File not open");
        }
    }

    void Replay::print()
    {
        // if replay on screen
        if (is_onscreen_replay)
            print_on_screen();

        // else replay on file
        else
            print_on_file();

        // close input file
        input_file.close();
    }

    void Replay::print_on_file()
    {
        output_file << "-----------REPLAY OF THE GAME-----------" << std::endl;

        // while loop
        while (!input_file.eof())
        {
            // print the state of chessboard
            output_file << this->board.snapshot() << std::endl;

            // make the move
            std::array<chessgame::Coordinates, 2> this_move = move();
            chessgame::Coordinates from{this_move[0]};
            chessgame::Coordinates to{this_move[1]};

            output_file << "Moved: " << this->board.get_piece(to)->getSymbol() << " from " << from.symbol << " to " << to.symbol << std::endl;
            output_file << "********************** End of turn **********************" << std::endl;
        }
        output_file << "********************** GAME OVER **********************" << std::endl;
        output_file.close();
    }

    void Replay::print_on_screen()
    {
        std::cout << "-----------REPLAY OF THE GAME-----------" << std::endl;
        
        // while loop input
        while (!input_file.eof())
        {
            // print the state of chessboard
            std::cout << this->board.snapshot() + "\n";

            // wait 1 second before the move
            std::this_thread::sleep_for(std::chrono::seconds(1));

            // make the move
            std::array<chessgame::Coordinates, 2> this_move = move();
            chessgame::Coordinates from{this_move[0]};
            chessgame::Coordinates to{this_move[1]};

            std::cout << "Moved: " << this->board.get_piece(to)->getSymbol() << " from " << from.symbol << " to " << to.symbol << std::endl;
            std::cout << "********************** End of turn **********************" << std::endl;
        }
        std::cout << "********************** GAME OVER **********************" << std::endl;
    }

    std::array<chessgame::Coordinates, 2> Replay::move()
    {
        // elements of the move:
        std::string initial;
        std::string final;
        char promotion_char;

        // get input
        this->input_file >> initial >> final >> promotion_char;
        chessgame::Coordinates from{initial};
        chessgame::Coordinates to{final};

        chessgame::check_coordinates(from);
        chessgame::check_coordinates(to);
        // if to is an empty cell
        if (!this->board.get_piece(to))
        {
            // if this is an enpassant or arrocco move
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
        if (from.x != to.x && !this->board.get_piece(to))
        {
            chessgame::Coordinates enpassant_coord{to.x, from.y};
            this->board.set_piece(enpassant_coord, nullptr);
        }
        // if not enpassant, this function does nothing
        return;
    }

    Replay::~Replay()
    {
        // close io streams
        if (this->input_file.is_open())
            this->input_file.close();
        if (this->output_file.is_open())
            this->output_file.close();
    }
}