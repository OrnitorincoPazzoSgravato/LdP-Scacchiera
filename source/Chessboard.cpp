#include "Utilities.h"
#include "Piece.h"
#include "Chessboard.h"
#include "Alfiere.h"
#include "Cavallo.h"
#include "Pedone.h"
#include "Re.h"
#include "Regina.h"
#include "Pedone.h"
#include "Torre.h"


namespace chessgame

{
    Chessboard::Chessboard()
    {
        initialize_black_pieces();
        initialize_blank_space();       
        initialize_white_pieces();        
    }                                        
    void Chessboard::set_piece(const Coordinates, const Piece& p)
    {}     
    Piece * Chessboard::get_piece(const Coordinates)
    {}                
    std::string& Chessboard::snapshot()
    {
        /*for (auto& rows : v)
        {
            for (auto&)
        }*/
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