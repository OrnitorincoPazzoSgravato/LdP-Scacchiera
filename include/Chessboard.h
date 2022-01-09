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

#include "Alfiere.h"
#include "Cavallo.h"
#include "Pedone.h"
#include "Re.h"
#include "Regina.h"
#include "Pedone.h"
#include "Torre.h"
#include "Utilities.h"
#include "Piece.h"





namespace chessgame

{
    constexpr unsigned int ROWS {8};
    constexpr unsigned int COLUMNS {8};
    constexpr unsigned int CELLS {64};
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
        *@brief copy constructor disabled, why would you need two Chessboards ?
        */  
        //Chessboard(Chessboard& c) = delete;
        /**
        *@brief set the cell [c.y][c.x] with p
        *
        *@param c the cell of the matrix we want to set
        *@param p  the pointer to the Piece we want to set
        *
        */                                            
        void set_piece(const Coordinates& c , Piece * p)
        {
           v[c.y][c.x].reset(p);
        }
        /**
        *@brief This function returns the Coordinates of an almost random piece of the chessboard
        *
        *@param pc the color of the Piece
        *@param from the Coordinates we start the iteration from
        *@param visited_cells the number of the cells we visited in the previous iterations
        * 
        *@return Coordinates of a piece of given color
        *
        */
        Coordinates& get_random(const PieceColor pc ,const Coordinates& from ,int& visited_cells);
        /**
        *@brief This function returns the pointer to the piece in [c.y][c.x]
        *
        *@param c the cell of the matrix we want to ispectionate
        *
        *@return  a pointer to the Piece in v(x,y)
        *@return  nullptr if there's no Piece in that cell
        *
        */               
        Piece * get_piece(const Coordinates& c)
        {
            return v[c.y][c.x].get();
        }
        /**
        * 
        *@brief This function create a snapshot of the state of the chessboard 
        *
        *@return the string of the state
        *
        */                   
        std::string& snapshot();
        /**
         * @brief it swaps the content of a cell at [from.y][from.x] and [to.y][to.x]
         * 
         * @param from description
         * 
         * @param to description
         */
        void swap_positions(const Coordinates& from,const Coordinates& to)
        {
            Piece * p1  {v[from.y][from.x].release()};
            Piece * p2 {v[to.y][to.x].release()};
            v[from.y][from.x].reset(p1);
            v[to.y][to.x].reset(p2);
        }                          
};
}

#endif 