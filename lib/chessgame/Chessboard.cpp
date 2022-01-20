/**
 * @file Chessboard.cpp
 * @author Enrico Cavinato
 * @version 0.1
 * @date 2022-01-06
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <memory>
#include <string>
#include <stdexcept>
#include <iostream>
#include <array>
#include <random>

#include "../../include/chessgame/Utilities.h"
#include "../../include/chessgame/Chessboard.h"
#include "../../include/chessgame/Cavallo.h"
#include "../../include/chessgame/Alfiere.h"
#include "../../include/chessgame/Regina.h"
#include "../../include/chessgame/Re.h"
#include "../../include/chessgame/Pedone.h"
#include "../../include/chessgame/Torre.h"

namespace chessgame

{
    Chessboard::Chessboard()
        : respawn_point{-1, -1}, limbo{nullptr}
    {
        // initialize black Pieces
        this->v[7][0] = std::make_unique<Torre>(BLACK, BLACK_TOWER);
        this->v[7][1] = std::make_unique<Cavallo>(BLACK, BLACK_HORSE);
        this->v[7][2] = std::make_unique<Alfiere>(BLACK, BLACK_BISHOP);
        this->v[7][3] = std::make_unique<Regina>(BLACK, BLACK_QUEEN);
        this->v[7][4] = std::make_unique<Re>(BLACK, BLACK_KING);
        this->v[7][5] = std::make_unique<Alfiere>(BLACK, BLACK_BISHOP);
        this->v[7][6] = std::make_unique<Cavallo>(BLACK, BLACK_HORSE);
        this->v[7][7] = std::make_unique<Torre>(BLACK, BLACK_TOWER);

        // for loop to initialize black Paws
        for (int i = 0; i < COLUMNS; i++)
        {
            this->v[6][i] = std::make_unique<Pedone>(BLACK, BLACK_PAW);
        }

        // initialize white Pieces

        // for loop to inizialize white Paws
        for (int i = 0; i < COLUMNS; i++)
        {
            this->v[1][i] = std::make_unique<Pedone>(WHITE, WHITE_PAW);
        }
        // initialize other white Pieces
        this->v[0][0] = std::make_unique<Torre>(WHITE, WHITE_TOWER);
        this->v[0][1] = std::make_unique<Cavallo>(WHITE, WHITE_HORSE);
        this->v[0][2] = std::make_unique<Alfiere>(WHITE, WHITE_BISHOP);
        this->v[0][3] = std::make_unique<Regina>(WHITE, WHITE_QUEEN);
        this->v[0][4] = std::make_unique<Re>(WHITE, WHITE_KING);
        this->v[0][5] = std::make_unique<Alfiere>(WHITE, WHITE_BISHOP);
        this->v[0][6] = std::make_unique<Cavallo>(WHITE, WHITE_HORSE);
        this->v[0][7] = std::make_unique<Torre>(WHITE, WHITE_TOWER);
    }

    std::string Chessboard::snapshot() const
    {
        std::string s = "  __________________________\n";

        // for loop rows
        int rows{ROWS};

        // print an inverted chessboard
        for (int i = ROWS -1; i >= 0; i--)
        {   
            // add row number
            s += std::to_string(rows) + " |";
            // for loop columns
            for (int j = 0; j < COLUMNS; j++)
            {
                Piece *p{this->v[i][j].get()};
                if (p) {
                    s += ' ';
                    s += p->getSymbol();
                    s += ' ';
                }
                else
                    s += "   ";
            }
            s += "|\n";
            rows--;
        }
        s += "  **************************\n";
        s += "    A  B  C  D  E  F  G  H";
        return s;
    }

    void Chessboard::set_piece(const Coordinates &c, Piece *p)
    {
        chessgame::check_coordinates(c);

        // save in limbo last removed piece or nullptr if the cell is empty
        // deallocation of Piece * which was in limbo take place when we use setpiece()
        this->limbo.reset(v[c.y][c.x].release());

        // sets respawn_point
        this->respawn_point = Coordinates(c.x, c.y);

        // sets the coordinates
        this->v[c.y][c.x].reset(p);
    }
    void Chessboard::swap_positions(const Coordinates &from, const Coordinates &to)
    {
        // check validity
        chessgame::check_coordinates(from);
        chessgame::check_coordinates(to);

        // Release pointers
        Piece *p1{v[from.y][from.x].release()};
        Piece *p2{v[to.y][to.x].release()};

        // Reset pointers
        this->v[from.y][from.x].reset(p2);
        this->v[to.y][to.x].reset(p1);
    }

    void check_coordinates(const Coordinates &coord)
    {
        if (coord.x >= COLUMNS || coord.y >= ROWS || coord.x < 0 || coord.y < 0)
            throw std::invalid_argument("Out of bound Coordinate");
    }

    void Chessboard::promote(char target_index, const Coordinates &coord)
    {
        // switch statement used to return the choosen derived class of Piece
        switch (target_index)
        {
        case BLACK_HORSE:
            v[coord.y][coord.x] = std::make_unique<Cavallo>(BLACK, BLACK_HORSE);
            break;
        case BLACK_BISHOP:
            v[coord.y][coord.x] = std::make_unique<Alfiere>(BLACK, BLACK_BISHOP);
            break;
        case BLACK_QUEEN:
            v[coord.y][coord.x] = std::make_unique<Regina>(BLACK, BLACK_QUEEN);
            break;
        case BLACK_TOWER:
            v[coord.y][coord.x] = std::make_unique<Torre>(BLACK, BLACK_TOWER);
            break;
        case WHITE_BISHOP:
            v[coord.y][coord.x] = std::make_unique<Alfiere>(WHITE, WHITE_BISHOP);
            break;
        case WHITE_HORSE:
            v[coord.y][coord.x] = std::make_unique<Cavallo>(WHITE, WHITE_HORSE);
            break;
        case WHITE_QUEEN:
            v[coord.y][coord.x] = std::make_unique<Regina>(WHITE, WHITE_QUEEN);
            break;
        case WHITE_TOWER:
            v[coord.y][coord.x] = std::make_unique<Torre>(WHITE, WHITE_TOWER);
            break;
        default:
            return;
        }
    }
}