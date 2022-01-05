/*

    @author: Enrico Cavinato
    @date: 2021-12-27

    This class represents a chessboard.

*/
#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include "../include/Alfiere.h"
#include "../include/Cavallo.h"
#include "../include/Pedone.h"
#include "../include/Re.h"
#include "../include/Regina.h"
#include "../include/Pedone.h"
#include "../include/Torre.h"
#include <string>
#include <memory>



namespace chessgame

{
constexpr int ROWS {8};
constexpr int COLUMNS {8};

class Chessboard {
private: 
    
    std::unique_ptr<Piece> v[ROWS][COLUMNS];
    void initialize_black_pieces();
    void initialize_white_pieces();
public:
    Chessboard()
    {
        initialize_black_pieces();      
        initialize_white_pieces();
    }
    /*
        @brief: set the cell [c.x][c.y] with p

        @arg: Coordinates& c the cell of the matrix we want to occupy
        @arg: Piece* p the pointer to the Piece we want to set

    */                                            
    void set_piece(const Coordinates& c , Piece * p)
    {
        v[c.x][c.y].reset(p);
    }
    /*

        @brief: This function returns the pointer to the piece in [c.x][c.y]

        @arg: Coordinates& c the cell of the matrix we want to ispectionate

        @return: Piece * a pointer to the Piece in v(x,y)
        @return nullptr if there's no Piece in that cell

    */               
    Piece * get_piece(const Coordinates& c)
    {
        return v[c.x][c.y].get();
    }
    /*

        @brief: This function create a snapshot of the state of the chessboard 

        @return: string& a reference to a string

    */                   
    std::string& snapshot();                                
};
}

#endif 