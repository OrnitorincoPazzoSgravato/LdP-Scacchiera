#include <iostream>
#include <string>

#include "../include/chessgame/Chessboard.h"

int main(int argc, char const *argv[])
{
    chessgame::Chessboard c;
    std::cout << c.snapshot();
    return 0;
}
