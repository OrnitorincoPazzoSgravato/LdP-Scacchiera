/**
 * @file Game.cpp
 * @author Riccardo Zuech
 * @brief 
 * @version 0.1
 * @date 2022-01-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "../include/Game.h";

#include <random>

#include "../include/Bot.h";
#include "../include/Utilities.h";
#include "../include/Chessboard.h";


namespace gameplay {
	
    // constructors declaration
    Game::Game() : n_moves{0}, en_passante_coord{nullptr}, board{chessgame::Chessboard()} {
        std::array<chessgame::PieceColor, 2> a_colors = this->getRandColors();
        this->p1 = chessgame::Player(a_colors[0]);
        this->p2 = chessgame::Bot(a_colors[1], this->board);
    }

    Game::Game(bool is_bot_match) : Game() {
        if(is_bot_match)
            this->p1 = chessgame::Bot(this->p1.getColor(), this->board);
    }

    // destructor declaration
    Game::~Game() {
        if(this->log_file.is_open()) this->log_file.close();
    }

    // private methods declaration
    std::array<chessgame::PieceColor, 2>& Game::getRandColors() {
        std::array<chessgame::PieceColor, 2> c_array; // declaration of the returned array

        double rand_num = std::rand();  // std library rand function to get a random number between 0 and 1
        // based on rand_num c_array is initialized with different values (just two possible outcomes, so an if-else is enough to cover them)
        if(rand_num < 0.5) c_array = {chessgame::PieceColor::BLACK, chessgame::PieceColor::WHITE};
        else c_array = {chessgame::PieceColor::WHITE, chessgame::PieceColor::BLACK};
        return c_array;
    }

    bool Game::writeLog(const std::string& move) {
        this->log_file << move << '\n';
    }

    // public methods declaration
    void Game::play() {
        this->log_file.open("game_log.txt"); // open the log file

        do {
            // holds the string representing the move to be logged
            std::string log_move;

            bool invalid_move = true;
            do {
                

            } while(invalid_move); // this cycle keeps going until a valid move has been entered

            this->log_file << log_move << '\n'; // outputs move to the log file

			std::cout << this->board.snapshot() << '\n';

            this->n_moves++; // increse number of moves

            this->current_turn = !this->current_turn; // alternates turns
        } while(false);

        this->log_file.close(); // closes the log file
    }
}