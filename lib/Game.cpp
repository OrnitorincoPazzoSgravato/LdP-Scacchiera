#include "../include/Game.h";
#include "../include/Player.h";
#include "../include/Bot.h";
#include "../include/Utilities.h";

#include <random>

std::array<chessgame::PieceColor&, 2> chessgame::Game::getRandColors() {
    std::array<chessgame::PieceColor&, 2> c_array; // declaration of the returned array

    double rand_num = std::rand();  // std library rand function to get a random number between 0 and 1
    // based on rand_num c_array is initialized with different values (just two possible outcomes, so an if-else is enough to cover them)
    if(rand_num < 0.5) c_array = {chessgame::PieceColor::BLACK, chessgame::PieceColor::WHITE};
    else c_array = {chessgame::PieceColor::WHITE, chessgame::PieceColor::BLACK};
    return c_array;
}

chessgame::Game::Game() {
    std::array<chessgame::PieceColor&, 2> a_colors = this->getRandColors();
    this->p1 = std::make_unique<chessgame::Player>(new chessgame::Player(a_colors[0]));
    this->p2 = std::make_unique<chessgame::Player>(new chessgame::Bot(a_colors[1]));

    this->board = chessgame::Chessboard();
    this->n_moves = 0;
}

chessgame::Game::Game(bool is_bot_match) : Game() {
    if(is_bot_match)
        this->p1.reset(new chessgame::Bot(p1.get()->pc));
}