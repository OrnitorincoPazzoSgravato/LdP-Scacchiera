#include <iostream>
#include "../include/Game.h"

// Riccardo Zuech

int main(int argc, char** argv) {
    if(argc != 2) return 0;
    char* mode = argv[1];
    bool is_bot_game = false;
    if(mode[0] != 'p' && mode[0] != 'c' && mode[1] != 'c') {
        std::cout << "Invalid argument. Pleasy use 'pc' or 'cc'.";
        return 0;
    }
    else if(mode[0] == 'c') is_bot_game = true;
    gameplay::Game game {is_bot_game};
    game.play();
    return 0;
}