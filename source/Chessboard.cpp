#include "../include/Piece.h"
#include "../include/Chessboard.h"
#include "../include/Alfiere.h"
#include "../include/Cavallo.h"
#include "../include/Pedone.h"
#include "../include/Re.h"
#include "../include/Regina.h"
#include "../include/Pedone.h"
#include "../include/Torre.h"
#include <string>
#include "../include/Utilities.h"

namespace chessgame

{
    Chessboard::Chessboard()
    {
        initialize_black_pieces();
        initialize_blank_space();       
        initialize_white_pieces();        
    }                                        
    void Chessboard::set_piece(const Coordinates c, Piece& p)
    {
        v[c.x][c.y] = &p;
    }     
    Piece * Chessboard::get_piece(const Coordinates c)
    {
        return v[c.x][c.y];
    }                
    std::string& Chessboard::snapshot()
    {
        string s;
        for (int i = 2; i < 6; i++)
        {
            /* code */
            for (int j = 0; i < COLUMNS; j++)
            {
                /* code */
                Piece * p = v[i][j];
                if (p == nullptr) s += " ";
                else s += p->getSymbol();
            }
            s += "\n";
            
        }
        return s;
    }
    void Chessboard::initialize_black_pieces()
    {
        v[0][0] = new Torre(BLACK,'T');
        v[0][1] = new Cavallo(BLACK,'C');
        v[0][2] = new Alfiere(BLACK ,'A');
        v[0][3] = new Regina(BLACK,'D');
        v[0][4] = new Re(BLACK,'R');
        v[0][5] = new Alfiere(BLACK,'A');
        v[0][6] = new Cavallo(BLACK,'C');
        v[0][7] = new Torre(BLACK,'T');
        for (int i = 0; i < COLUMNS; i++)
        {
            /* code */
            v[1][i] = new Pedone(BLACK,'P');
        }
            
    }
    void Chessboard::initialize_white_pieces()
    {
        for (int i = 0; i < COLUMNS; i++)
        {
            /* code */
            v[6][i] = new Pedone(WHITE,'p');
        }
        v[7][0]  = new Torre(WHITE,'t');
        v[7][1] = new Cavallo(WHITE,'c');
        v[7][2] = new Alfiere(WHITE ,'a');
        v[7][3] = new Regina(WHITE,'d');
        v[7][4] = new Re(WHITE,'r');
        v[7][5] = new Alfiere(WHITE,'a');
        v[7][6] = new Cavallo(WHITE,'c');
        v[7][7] = new Torre(WHITE,'t');
        
    }
    void Chessboard::initialize_blank_space()
    {
        int i {2};
        for (int j = 0; j < COLUMNS || i<6; j++)
        {
            /* code */
            if (j == 7) 
            {
                j =0;
                i++;
            }
            v[i][j] = nullptr;

        }
    }

    Chessboard::~Chessboard()
    {
        for (int i = 0; i < ROWS; i++)
        {
            /* code */
            for (int j = 0; i < COLUMNS; j++)
            {
                /* code */
                delete v[i][j]; 
            }
            
        }
        
    }
}