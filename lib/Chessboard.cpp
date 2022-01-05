
#include "../include/Chessboard.h"

namespace chessgame

{
    Chessboard::Chessboard()
    {
        initialize_black_pieces();
        initialize_blank_space();       
        initialize_white_pieces();        
    } 
        /*

        @arg: Coordinates& c the cell of the matrix we want to occupy
        @arg: Piece* p the pointer to the Piece we want to set

        @return: Piece * a pointer to the initial content of the cell: if it was empty returns nullptr

    */                                         
    Piece * Chessboard::set_piece(const Coordinates& c, Piece* p)
    {
        Piece * pointer {v[c.x][c.y]};
        v[c.x][c.y] = p;
        return pointer;

    }
        /*

        @arg: Coordinates& c the cell of the matrix we want to get

        @return: Piece * a pointer to the Piece in v(x,y), may return nullptr if there's no Piece

    */         
    Piece * Chessboard::get_piece(const Coordinates& c)
    {
        return v[c.x][c.y];
    }
    /*

        This function create a snapshot of the state of the chessboard 

        @return: string& a reference to a string

    */            
    std::string& Chessboard::snapshot()
    {
        string s;
        // for loop for rows
        int num {8};
        for (int i = 0; i < ROWS; i++)
        {
            s += num + " ";
            // for loop columns
            for (int j = 0; i < COLUMNS; j++)
            {
                Piece * p = v[i][j];
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
            v[6][i] = new Pedone(WHITE,'p');
        }
        // initialize other Pieces in free store 
        v[7][0]  = new Torre(WHITE,'t');
        v[7][1] = new Cavallo(WHITE,'c');
        v[7][2] = new Alfiere(WHITE ,'a');
        v[7][3] = new Regina(WHITE,'d');
        v[7][4] = new Re(WHITE,'r');
        v[7][5] = new Alfiere(WHITE,'a');
        v[7][6] = new Cavallo(WHITE,'c');
        v[7][7] = new Torre(WHITE,'t');
        
    }
    /*

        This private function sets blank space when the chessboard is created 

        @return: void

    */
    void Chessboard::initialize_blank_space()
    {
        // for loop rows, from the third to the sixth
        for (int i = 2; i < 6 ; i++)
        {
            // for loop for columns
            for (int j = 0; j < COLUMNS; j++)
            {
                v[i][j] = nullptr;
            }
        }
    }
    /*

        This function implements the act of capture

        @arg: const Coordinates& c  coordinates of the piece we want to be captured
        @arg: Piece * pi piece we want to capture

        @return: void

    */
    void Chessboard::capture(const Coordinates& c , Piece * pi)
    {
        // get the pointer to the piece we want to be captured
        Piece* piece {get_piece(c)};
        // set the new piece 
        set_piece(c,pi);
        // delete the captured piece
        delete piece;
    }

    Chessboard::~Chessboard()
    {
        for (int i = 0; i < ROWS; i++)
        {
            /* code */
            for (int j = 0; i < COLUMNS; j++)
            {
                /* code */
                Piece * des {v[i][j]};
                if (des) delete des;
            }
            
        }
        
    }
}