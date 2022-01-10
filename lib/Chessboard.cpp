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

#include "../include/Utilities.h"
#include "../include/Chessboard.h"
#include "../include/Cavallo.h"
#include "../include/Alfiere.h"
#include "../include/Regina.h"
#include "../include/Re.h"
#include "../include/Pedone.h"
#include "../include/Torre.h"

namespace chessgame

{    
    using std::make_unique;
    using std::string;

    Chessboard::Chessboard()
    {
        // initialize black Pieces  
        this->v[0][0]= make_unique<Torre>( BLACK, 'T' );
        this->v[0][1]= make_unique<Cavallo>( BLACK,'C')  ;
        this->v[0][2]= make_unique<Alfiere>( BLACK,'A')  ;
        this->v[0][3]= make_unique<Regina>( BLACK,'D')  ;
        this->v[0][4]= make_unique<Re>( BLACK,'R')  ;
        this->v[0][5]= make_unique<Alfiere>( BLACK,'A')  ;
        this->v[0][6]= make_unique<Cavallo>( BLACK,'C')  ;
        this->v[0][7] = make_unique<Torre>( BLACK, 'T' );

        //for loop to initialize black Paws
        for (int i = 0; i < COLUMNS; i++)
        {
            this->v[1][i]= make_unique<Pedone>( BLACK, 'P' );
        }

        //initialize white Pieces

        // for loop to inizialize white Paws
        for (int i = 0; i < COLUMNS; i++)
        {
            this->v[6][i]= make_unique<Pedone>( WHITE, 'p' );
        }
        // initialize other white Pieces
        this->v[7][0]= make_unique<Torre>( WHITE, 't' );
        this->v[7][1]= make_unique<Cavallo>( WHITE, 'c' );
        this->v[7][2]= make_unique<Alfiere>( WHITE, 'a' );
        this->v[7][3]= make_unique<Regina>( WHITE, 'd' );
        this->v[7][4]= make_unique<Re>( WHITE, 'r' );
        this->v[7][5]= make_unique<Alfiere>( WHITE, 'a' );
        this->v[7][6]= make_unique<Cavallo>( WHITE, 'c' );
        this->v[7][7]= make_unique<Torre>( WHITE, 't' );

    }                               
           
    std::string& Chessboard::snapshot()
    {
        string s;
        // for loop rows
        int num { 8 };
        for ( int i = 0 ; i < ROWS; i++ )
        {
            s += num + " ";
            // for loop columns
            for ( int j = 0; i < COLUMNS; j++ )
            {
                Piece * p  {this->v[i][j].get()} ;
                if (p) s += p->getSymbol() ;
                else s += " ";
            }
            s += "\n";
            num--;           
        }
        s += "\nABCDEFGH";
        return s;
    }
    Coordinates& Chessboard::get_random(const PieceColor pc,const Coordinates& from ,int& count)
    {
        unsigned int row {from.y};
        unsigned int column {from.x};
        // while loop inspects at worst every cell one time and stops if a valid move does not exist
        while (count <= CELLS)
        {
            // increment of the number of pieces we visited
            count++;
            // if we finished to visit a row we pass to the next
            if (column == COLUMNS) 
            {
                column = 0;
                row++;
            }
            // if we finished to visit the matrix, we start from (0,0)
            if (row == ROWS) row = 0;
            // if the piece in the considered cell contains a piece of given color
            if ( this->v[row][column].get()->getColor() == pc )
            {
                Coordinates c {column,row};
                return c;
            }
            column++;
        }
        // if a valid piece does not exist
        Coordinates c {-1,-1};
        return c;
        
    }
    void Chessboard::set_piece(const Coordinates& c , Piece * p)
        {
            // saves in limbo last deleted piece 
            this->limbo.reset(v[c.y][c.x].release());

            // sets respawn_point
            this->respawn_point = Coordinates(c.x, c.y);

            // sets the coordinates
            this->v[c.y][c.x].reset(p);
        }
    void Chessboard::swap_positions(const Coordinates& from,const Coordinates& to)
        {
            //Release pointers 
            Piece * p1  {v[from.y][from.x].release()};
            Piece * p2 {v[to.y][to.x].release()};

            //Reset pointers
            this->v[from.y][from.x].reset(p1);
            this->v[to.y][to.x].reset(p2);
        }
}