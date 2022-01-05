#include "../include/Game.h";
#include "../include/Player.h";
#include "../include/Bot.h";
#include "../include/Utilities.h";

#include <random>

// private methods declaration
std::array<chessgame::PieceColor&, 2> chessgame::Game::getRandColors() {
    std::array<chessgame::PieceColor&, 2> c_array; // declaration of the returned array

    double rand_num = std::rand();  // std library rand function to get a random number between 0 and 1
    // based on rand_num c_array is initialized with different values (just two possible outcomes, so an if-else is enough to cover them)
    if(rand_num < 0.5) c_array = {chessgame::PieceColor::BLACK, chessgame::PieceColor::WHITE};
    else c_array = {chessgame::PieceColor::WHITE, chessgame::PieceColor::BLACK};
    return c_array;
}

bool chessgame::Game::writeLog(const std::string& move) {
    this->log_file << move << '\n';
}

bool chessgame::Game::isGameOver() {
    // TBD
    return false;
}

// constructors declaration
chessgame::Game::Game() : n_moves{0} {
    std::array<chessgame::PieceColor&, 2> a_colors = this->getRandColors();
    this->p1 = std::make_unique<chessgame::Player>(new chessgame::Player(a_colors[0]));
    this->p2 = std::make_unique<chessgame::Player>(new chessgame::Bot(a_colors[1]));

    this->board = chessgame::Chessboard();
}

chessgame::Game::Game(bool is_bot_match) : Game() {
    if(is_bot_match)
        this->p1.reset(new chessgame::Bot(p1.get()->pc));
}

// destructor declaration
chessgame::Game::~Game() {
    if(this->log_file.is_open()) this->log_file.close();
}

// public methods declaration
void chessgame::Game::play() {
    this->log_file.open("game_log.txt"); // open the log file

    do {
        // TBD
    } while(!this->isGameOver());

    this->log_file.close(); // closes the log file
}