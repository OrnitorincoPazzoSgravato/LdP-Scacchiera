
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
    class Piece;

    // constants of the chessboard: number of rows,columns and cells
    constexpr unsigned int ROWS {8};
    constexpr unsigned int COLUMNS {8};
    constexpr unsigned int CELLS {64};


    /**
	 * @brief This class implements a chessboard
     *  
	 */
    class Chessboard {
    public:
        /**
         * @brief Construct a new Chessboard object
         * 
         */
        Chessboard();

        /**
        *@brief Set the cell [c.y][c.x] with p, reset limbo with p and set respawn_place to c
        *
        *@param c the cell of the matrix we want to set
        *@param p  the pointer to the Piece we want to set
        */                                            
        void set_piece(const Coordinates& c , Piece * p);
        /**
        *@brief This function returns the Coordinates of an almost random piece of the chessboard
        *
        *@param pc the color of the Piece
        *@param from the Coordinates we start the iteration from
        *@param visited_cells the number of the cells we visited in the previous iterations
        * 
        *@return Coordinates of a piece of given color
        */
        Coordinates get_random(const PieceColor pc ,const Coordinates& from ,int& visited_cells);
        /**
        *@brief This function returns the pointer to the piece in [c.y][c.x]
        *
        *@param c the cell of the matrix we want to ispectionate
        *
        *@return  a pointer to the Piece in v(x,y)
        *@return  nullptr if there's no Piece* in that cell
        *
        */               
        Piece * get_piece(const Coordinates& c){
            return v[c.y][c.x].get();
        }
        /**
        * 
        *@brief This function create a snapshot of the state of the chessboard 
        *
        *@return the string of the state
        */                   
        std::string snapshot();
        /**
         * @brief Swap the content of a cell at [from.y][from.x] and [to.y][to.x]
         * 
         * @param from Coordinates of first piece
         * 
         * @param to  Coordinates of second piece
         */
        void swap_positions(const Coordinates& from,const Coordinates& to);
        /**
         * @brief Undo the last setPiece(). Be careful when you use it!
         */
        void restore_setPiece(){
            this->v[this->respawn_point.y][this->respawn_point.x].reset(limbo.release());
        }
    private: 

        //This variable implements the matrix: chessgame::Chesboard guarantees an incapsulation of this bidimensional array
        std::unique_ptr<Piece> v[ROWS][COLUMNS];

        //Limbo is the variable which owns a Piece* when it is removed from the chessboard: we want to implement the posibility of restore the remotion
        std::unique_ptr<Piece> limbo;

        //This Coordinates represents the cell where the Piece* owned by limbo was before the remotion
        Coordinates respawn_point;

        //checks if the coordinates are out of bounds

        void check_coordinates(int x, int y ); 
};
}

#endif 