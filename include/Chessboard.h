/**
 * @file Chessboard.h
 * @author Enrico Cavinato
 * @brief 
 * @version 0.1
 * @date 2022-12-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <string>
#include <memory>

#include "../include/Alfiere.h"
#include "../include/Cavallo.h"
#include "../include/Pedone.h"
#include "../include/Re.h"
#include "../include/Regina.h"
#include "../include/Pedone.h"
#include "../include/Torre.h"
#include "../include/Utilities.h"
#include "../include/Piece.h"




namespace chessgame

{
    constexpr int ROWS {8};
    constexpr int COLUMNS {8};
    /**
	 * @brief Classe che rappresenta una scacchiera.
	 * Si occupa della sua inizializzazione, di settare e restituire le pedine, senza check
	 */
    class Chessboard {
    private: 
    
        std::unique_ptr<Piece> v[ROWS][COLUMNS];
    public:
        Chessboard();
        /**
        *@brief: set the cell [c.x][c.y] with p
        *
        *@arg: Coordinates& c the cell of the matrix we want to occupy
        *@arg: Piece* p the pointer to the Piece we want to set
        *
        */                                            
        void set_piece(const Coordinates& c , Piece * p)
        {
           v[c.x][c.y].reset(p);
        }
        /**
        *@brief: This function returns the pointer to the piece in [c.x][c.y]
        *
        @arg: Coordinates& c the cell of the matrix we want to ispectionate
        *
        *@return: Piece * a pointer to the Piece in v(x,y)
        *@return nullptr if there's no Piece in that cell
        *
        */               
        Piece * get_piece(const Coordinates& c)
        {
            return v[c.x][c.y].get();
        }
        /**
        * 
        *@brief: This function create a snapshot of the state of the chessboard 
        *
        *@return: string& a reference to a string
        *
        */                   
        std::string& snapshot();                                
};
}

#endif 