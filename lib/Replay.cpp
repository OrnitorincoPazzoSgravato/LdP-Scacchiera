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
#include <chrono>
#include <thread>
#include <stdexcept>
#include <iostream>

#include "../include/Replay.h"
#include "../include/Game.h"
#include "../include/chessgame/Utilities.h"
#include "../include/chessgame/Chessboard.h"
#include "../include/chessgame/Human.h"

namespace replay_game
{
    static const std::string gameover_string{"********************** GAME OVER **********************"};

    void Replay::print()
    {
        // open input file and checks if open
        input_file.open(inputstring, std::fstream::in);
        if (!input_file)
            throw std::invalid_argument("This file does not exist or not open properly");

        // if this is a onscreen replay
        if (is_onscreen_replay)
            print_on_screen();
        else
        {
            // open output file and check if output file is open
            output_file.open(outputstring, std::fstream::out);
            if (!output_file.is_open())
                throw std::invalid_argument("File not open");

            // print and close output
            print_on_file();
            output_file.close();
        }
        // close input
        input_file.close();
    }

    void Replay::print_on_file()
    {
        int turn{0};
        output_file << "-----------REPLAY OF THE GAME-----------" << std::endl
                    << this->board.snapshot() << std::endl;

        // while loop
        while (!input_file.eof())
        {
            // next turn
            turn++;
            output_file << "********************** Turn " << turn << " **********************" << std::endl;

            // make the move
            std::array<chessgame::Coordinates, 2> this_move = move();
            std::string from{this_move[0].symbol}, to{this_move[1].symbol};

            // print checkmate contition
            char checkmate_char{'x'};
            int end_of_game{-1};
            this->input_file >> checkmate_char >> end_of_game;
            output_file << kingcheck_string(checkmate_char) << std::endl;

            // print state of chessboard
            output_file << this->board.snapshot() << std::endl;

            output_file << "Moved: " << this->board.get_piece(to)->getSymbol() << " from " << from << " to " << to << std::endl;
            output_file << "********************** End of turn " << turn << " **********************" << std::endl;
            output_file << end_of_game_check(end_of_game) << std::endl;

            // if game ended
            if (end_of_game != 0)
                break;
        }
        output_file << gameover_string << std::endl;
    }

    void Replay::print_on_screen()
    {
        std::cout << "-----------REPLAY OF THE GAME-----------\n"
                  << this->board.snapshot() << "\n";
        int turn{0};

        // while loop input
        while (!input_file.eof())
        {
            turn++;
            // wait 1 second before the move
            std::this_thread::sleep_for(std::chrono::seconds(1));
            std::cout << "********************** Turn " << turn << " **********************\n";

            // make the move
            std::array<chessgame::Coordinates, 2> this_move = move();
            std::string from{this_move[0].symbol}, to{this_move[1].symbol};

            // print the state of chessboard
            std::cout << this->board.snapshot() + "\n";

            // print check contition and game over condition
            char checkmate_flag{'x'};
            int end_of_game{-1};
            this->input_file >> checkmate_flag >> end_of_game;
            std::cout << kingcheck_string(checkmate_flag) << "\n";

            std::cout << "Moved: " << this->board.get_piece(to)->getSymbol() << " from " << from << " to " << to << std::endl;
            std::cout << "********************** End of turn " << turn << " **********************\n";
            std::cout << end_of_game_check(end_of_game) << "\n";

            // if game ended
            if (end_of_game != 0)
                break;
        }
        std::cout << gameover_string;
    }

    std::array<chessgame::Coordinates, 2> Replay::move()
    {
        // elements of the move:
        std::string initial, final;
        char promotion_char;

        // get input
        this->input_file >> initial >> final >> promotion_char;
        check_input_from_file(initial, final);

        chessgame::Coordinates from{initial}, to{final};

        //if (!this->board.get_piece(from))
          //  throw std::invalid_argument("This move does not exist: no piece in from");

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

    void Replay::arrocco_move(const chessgame::Coordinates &from, const chessgame::Coordinates &to)
    {
        // if is not arrocco, return
        bool is_arrocco {gameplay::isArrocco(std::array<chessgame::Coordinates, 2>{from, to}, board)};
        if (!is_arrocco)
            return;
        // case 1 : black king to the left
        if (to.symbol == "C8")
            this->board.swap_positions(T_sinistra, chessgame::Coordinates{"D8"});
        // case 2 :black king to the right
        else if (to.symbol == "G8")
            this->board.swap_positions(T_destra, chessgame::Coordinates{"F8"});

        // case 3: white king to the left
        else if (to.symbol == "C1")
            this->board.swap_positions(t_sinistra, chessgame::Coordinates{"D1"});

        // case 4 :white king to the right
        else if (to.symbol == "G1")
            this->board.swap_positions(chessgame::Coordinates{"F1"}, t_destra);
    }

    void Replay::en_passant_capture(const chessgame::Coordinates &from, const chessgame::Coordinates &to)
    {
        // if column is different but cell is empty: this implementation implies that the replay is from
        // a valid move
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

    std::string kingcheck_string(char check_flag)
    {
        switch (check_flag)
        {
        case '0':
            return "White player is in check";
        case '1':
            return "Black player is in check";
        case '*':
            return "";
        default:
            throw std::invalid_argument("Invalid input for check in log file");
        }
    }

    std::string end_of_game_check(int i)
    {
        switch (i)
        {
        case 0:
            return "";
        case 1:
            return "Game Over: the game is a draw.";
        case 2:
            return "It's a checkmate, white player won!";
        case 3:
            return "It's a checkmate, black player won!";

        default:
            throw std::invalid_argument("Invalid input in log file");
        }
    }

    void check_input_from_file(const std::string &initial, const std::string &final)
    {
        // check if the move is in a valid form
        bool valid_formula{chessgame::check_move(std::array<std::string, 2>{initial, final})};

        // no lowercase
        bool initial_lowercase{initial[0] >= 'a' && initial[0] <= 'h'};
        bool final_lowercase{final[0] >= 'a' && final[0] <= 'h'};

        // if move is invalid exception
        if (!valid_formula || initial_lowercase || final_lowercase)
            throw std::invalid_argument("Invalid string in log file");
    }
}