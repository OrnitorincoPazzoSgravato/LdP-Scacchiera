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
    Chessboard::Chessboard() : respawn_point{-1,-1},limbo{nullptr}
    {
        // initialize black Pieces
        this->v[0][0] = std::make_unique<Torre>(BLACK, 'T');
        this->v[0][1] = std::make_unique<Cavallo>(BLACK, 'C');
        this->v[0][2] = std::make_unique<Alfiere>(BLACK, 'A');
        this->v[0][3] = std::make_unique<Regina>(BLACK, 'D');
        this->v[0][4] = std::make_unique<Re>(BLACK, 'R');
        this->v[0][5] = std::make_unique<Alfiere>(BLACK, 'A');
        this->v[0][6] = std::make_unique<Cavallo>(BLACK, 'C');
        this->v[0][7] = std::make_unique<Torre>(BLACK, 'T');

        //for loop to initialize black Paws
        for (int i = 0; i < COLUMNS; i++)
        {
            this->v[1][i] = std::make_unique<Pedone>(BLACK, 'P');
        }

        //initialize white Pieces

        // for loop to inizialize white Paws
        for (int i = 0; i < COLUMNS; i++)
        {
            this->v[6][i] = std::make_unique<Pedone>(WHITE, 'p');
        }
        // initialize other white Pieces
        this->v[7][0] = std::make_unique<Torre>(WHITE, 't');
        this->v[7][1] = std::make_unique<Cavallo>(WHITE, 'c');
        this->v[7][2] = std::make_unique<Alfiere>(WHITE, 'a');
        this->v[7][3] = std::make_unique<Regina>(WHITE, 'd');
        this->v[7][4] = std::make_unique<Re>(WHITE, 'r');
        this->v[7][5] = std::make_unique<Alfiere>(WHITE, 'a');
        this->v[7][6] = std::make_unique<Cavallo>(WHITE, 'c');
        this->v[7][7] = std::make_unique<Torre>(WHITE, 't');
    }

    std::string Chessboard::snapshot()
    {
        std::string s;
        // for loop rows
        int num{8};
        for (int i = 0; i < ROWS; i++)
        {
            s += std::to_string(num) + " ";
            // for loop columns
            for (int j = 0; j < COLUMNS; j++)
            {
                Piece *p{this->v[i][j].get()};
                if (p)
                    s += p->getSymbol();
                else
                    s += " ";
            }
            s += "\n";
            num--;
        }
        s += "  ABCDEFGH";
        return s;
    }
    std::array<Coordinates,2> Chessboard::get_random(const PieceColor pc)
    {
        // generate the coordinates of a random cell we want to visit
        int row{std::rand() % ROWS};
        int column{std::rand() % COLUMNS};

        // count cells
        int count {0};

        // while loop inspects at worst all cells: a valid move must exist because of checkmate condition
        while (count < CELLS)
        {
            // increment of the number of pieces we visited
            count++;
            column++;

            // if we finished to visit a row we pass to the next
            if (column == COLUMNS)
            {
                column = 0;
                row++;
            }
            // if we get out of bounds we restart from (0,0)
            if (row == ROWS)
                row = 0;
            // if the piece in the considered cell contains a piece of given color
            if (v[row][column].get() && this->v[row][column].get()->getColor() == pc)
            {
                Coordinates from{column, row};
                // get the possible moves
                std::vector<Coordinates> possible_moves{this->get_piece(from)->getMoves(*this, from)};
                
                // if a valid move does not exist
                if (possible_moves.size() == 0) continue;

                // if a valid move does exist
                Coordinates to {possible_moves[0]};
                return std::array<Coordinates,2> {from,to};
            }
        }
        // if a valid piece does not exist
        //return 0 ;
    }
    void Chessboard::set_piece(const Coordinates &c, Piece *p)
    {
        this->check_coordinates(c);
        // saves in limbo last deleted piece or nullptr il the cell is empty
        // the deallocation of Piece * which was in limbo take place when we use setpiece()
        this->limbo.reset(v[c.y][c.x].release());

        // sets respawn_point
        this->respawn_point = Coordinates(c.x, c.y);

        // sets the coordinates
        this->v[c.y][c.x].reset(p);
    }
    void Chessboard::swap_positions(const Coordinates &from, const Coordinates &to)
    {
        // check validity
        this->check_coordinates(from);
        this->check_coordinates(to);

        //Release pointers
        Piece *p1{v[from.y][from.x].release()};
        Piece *p2{v[to.y][to.x].release()};

        //Reset pointers
        this->v[from.y][from.x].reset(p1);
        this->v[to.y][to.x].reset(p2);
    }

    void Chessboard::check_coordinates(const Coordinates& coord)
    {
        if (coord.x >= COLUMNS || coord.y >= ROWS || coord.x < 0  || coord.y < 0 )
            throw std::invalid_argument( "Out of bound Coordinate" );
    }
    
    void Chessboard::promote(char target_index,const Coordinates& coord)
    {
        // switch statement used to return the choosen derived class of Piece
        switch (target_index)
        {
        case 'C':
            v[coord.y][coord.x] = std::make_unique<Cavallo>(BLACK, 'C');
            break;
        case 'A':
            v[coord.y][coord.x] = std::make_unique<Alfiere>(BLACK, 'A');
            break;
        case 'D':
            v[coord.y][coord.x] = std::make_unique<Regina>(BLACK, 'D');
            break;
        case 'T':
            v[coord.y][coord.x] = std::make_unique<Torre>(BLACK, 'T');
            break;
        case 'a':
            v[coord.y][coord.x] = std::make_unique<Alfiere>(WHITE, 'a');
            break;
        case 'c':
            v[coord.y][coord.x] = std::make_unique<Cavallo>(WHITE, 'c');
            break;
        case 'd':
            v[coord.y][coord.x] = std::make_unique<Regina>(WHITE, 'd');
            break;
        case 't':
            v[coord.y][coord.x] = std::make_unique<Torre>(WHITE, 't');
            break;
        default:
            return;
        }
    }
}