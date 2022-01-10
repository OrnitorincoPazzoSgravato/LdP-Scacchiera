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
        v[0][0] = make_unique<Torre>( BLACK, 'T' );
        v[0][1]= make_unique<Cavallo>( BLACK,'C')  ;
        v[0][2]= make_unique<Alfiere>( BLACK,'A')  ;
        v[0][3]= make_unique<Regina>( BLACK,'D')  ;
        v[0][4]= make_unique<Re>( BLACK,'R')  ;
        v[0][5]= make_unique<Alfiere>( BLACK,'A')  ;
        v[0][6]= make_unique<Cavallo>( BLACK,'C')  ;
        v[0][7] = make_unique<Torre>( BLACK, 'T' );
        //for loop to initialize black Pedones
        for (int i = 0; i < COLUMNS; i++)
        {
            v[1][i]= make_unique<Pedone>( BLACK, 'P' );
        }

        //initialize white Pieces

        // for loop to inizialize white Pedones
        for (int i = 0; i < COLUMNS; i++)
        {
            v[6][i]= make_unique<Pedone>( WHITE, 'p' );
        }
        // initialize other white Pieces
        v[7][0]= make_unique<Torre>( WHITE, 't' );
        v[7][1]= make_unique<Cavallo>( WHITE, 'c' );
        v[7][2]= make_unique<Alfiere>( WHITE, 'a' );
        v[7][3]= make_unique<Regina>( WHITE, 'd' );
        v[7][4]= make_unique<Re>( WHITE, 'r' );
        v[7][5]= make_unique<Alfiere>( WHITE, 'a' );
        v[7][6]= make_unique<Cavallo>( WHITE, 'c' );
        v[7][7]= make_unique<Torre>( WHITE, 't' );

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
                Piece * p  {v[i][j].get()} ;
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
            if ( v[row][column].get()->getColor() == pc )
            {
                return Coordinates(column,row);
            }
            column++;
        }
        // if a valid piece does not exist
        return Coordinates(-1,-1);
        
    }
}