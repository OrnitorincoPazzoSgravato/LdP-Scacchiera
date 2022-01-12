#include <iostream>
#include <string>

#include "../include/chessgame/Chessboard.h"
#include "../include/chessgame/Piece.h"
#include "../include/chessgame/Utilities.h"
#include "../include/chessgame/Cavallo.h"
#include "../include/chessgame/Torre.h"
#include "../include/chessgame/Re.h"
#include "../include/chessgame/Regina.h"
#include "../include/chessgame/Pedone.h"
#include "../include/chessgame/Alfiere.h"

int main()
{
    chessgame::Chessboard c;
    std::cout << c.snapshot();
    return 0;
}
