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

#include "../include/Utilities.h"
#include "../include/Chessboard.h"

namespace chessgame

{    
    using namespace std;

    Chessboard::Chessboard()
    {
        // initialize black Pieces  
        v[0][0] = std::make_unique<Torre>( BLACK, 'T' );
        v[0][1].reset(new Cavallo( BLACK,' C ') )  ;
        v[0][2].reset(new Alfiere( BLACK , ' A ' ) ) ;
        v[0][3].reset(new Regina( BLACK, ' D ' ) )  ;
        v[0][4].reset(new Re(BLACK,'R'))  ;
        v[0][5].reset(new Alfiere(BLACK,'A'))  ;
        v[0][6].reset(new Cavallo(BLACK,'C'))  ;
        v[0][7].reset(new Torre(BLACK,'T'))  ;
        //for loop to initialize black Pedones
        for (int i = 0; i < COLUMNS; i++)
        {
            v[1][i].reset(new Pedone(BLACK,'P'));
        }

        //initialize white Pieces

        // for loop to inizialize white Pedones
        for (int i = 0; i < COLUMNS; i++)
        {
            v[6][i].reset(new Pedone(WHITE,'p'));
        }
        // initialize other white Pieces
        v[7][0].reset(new Torre(WHITE,'t'));
        v[7][1].reset(new Cavallo(WHITE,'c'));
        v[7][2].reset(new Alfiere(WHITE ,'a'));
        v[7][3].reset(new Regina(WHITE,'d')) ;
        v[7][4].reset(new Re(WHITE,'r')) ;
        v[7][5].reset(new Alfiere(WHITE,'a')) ;
        v[7][6].reset(new Cavallo(WHITE,'c')) ;
        v[7][7].reset(new Torre(WHITE,'t'));

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
                Piece * p = v[i][j].get() ;
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