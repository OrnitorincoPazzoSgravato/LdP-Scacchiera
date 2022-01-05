
#include "../include/Chessboard.h"

namespace chessgame

{
    Chessboard::Chessboard()
    {
        initialize_black_pieces();      
        initialize_white_pieces();        
    } 
        /*

        @arg: Coordinates& c the cell of the matrix we want to occupy
        @arg: Piece* p the pointer to the Piece we want to set

        @return: Piece * a pointer to the initial content of the cell: if it was empty returns nullptr

    */                                         
    void Chessboard::set_piece(const Coordinates& c, Piece* p)
    {
        v[c.x][c.y].reset(p);

    }
        /*

        @arg: Coordinates& c the cell of the matrix we want to get

        @return: Piece * a pointer to the Piece in v(x,y), may return nullptr if there's no Piece

    */         
    Piece * Chessboard::get_piece(const Coordinates& c)
    {
        return v[c.x][c.y].get();
    }
    /*

        This function create a snapshot of the state of the chessboard 

        @return: string& a reference to a string

    */            
    std::string& Chessboard::snapshot()
    {
        string s;
        // for loop rows
        int num {8};
        for (int i = 0; i < ROWS; i++)
        {
            s += num + " ";
            // for loop columns
            for (int j = 0; i < COLUMNS; j++)
            {
                Piece * p = v[i][j].get();
                if (p) s += p->getSymbol();
                else s += " ";
            }
            s += "\n";
            num--;           
        }
        s += "\nABCDEFGH";
        return s;
    }
    /*

        This private function initialize black pieces when the chessboard is created 

        @return: void

    */
    void Chessboard::initialize_black_pieces()
    {
        v[0][0].reset(new Torre(BLACK,'T'))  ;
        v[0][1].reset(new Cavallo(BLACK,'C'))  ;
        v[0][2].reset(new Alfiere(BLACK ,'A')) ;
        v[0][3].reset(new Regina(BLACK,'D'))  ;
        v[0][4].reset(new Re(BLACK,'R'))  ;
        v[0][5].reset(new Alfiere(BLACK,'A'))  ;
        v[0][6].reset(new Cavallo(BLACK,'C'))  ;
        v[0][7].reset(new Torre(BLACK,'T'))  ;
        for (int i = 0; i < COLUMNS; i++)
        {
            /* code */
            v[1][i].reset(new Pedone(BLACK,'P'));
        }
            
    }
    /*

        This private function initialize white pieces when the chessboard is created 

        @return: void

    */
    void Chessboard::initialize_white_pieces()
    {
        // for loop to inizialize Pedone
        for (int i = 0; i < COLUMNS; i++)
        {
            /* code */
            v[6][i].reset(new Pedone(WHITE,'p'));
        }
        // initialize other Pieces in free store 
        v[7][0].reset(new Torre(WHITE,'t'));
        v[7][1].reset(new Cavallo(WHITE,'c'));
        v[7][2].reset(new Alfiere(WHITE ,'a'));
        v[7][3].reset(new Regina(WHITE,'d')) ;
        v[7][4].reset(new Re(WHITE,'r')) ;
        v[7][5].reset(new Alfiere(WHITE,'a')) ;
        v[7][6].reset(new Cavallo(WHITE,'c')) ;
        v[7][7].reset(new Torre(WHITE,'t'));
        
    }
}