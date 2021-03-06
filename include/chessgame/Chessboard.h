/**
 * @file Chessboard.h
 * @author Enrico Cavinato
 * @brief The concept of a real life Chessboard
 * @version 0.1
 * @date 2022-01-12
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
    // forward declaration
    class Piece;

    // constants of the chessboard: number of rows,columns and cells
    constexpr int ROWS{8};
    constexpr int COLUMNS{8};
    constexpr int CELLS{64};

    constexpr char BLACK_BISHOP{'A'};
    constexpr char WHITE_BISHOP{'a'};

    constexpr char BLACK_HORSE{'C'};
    constexpr char WHITE_HORSE{'c'};

    constexpr char WHITE_QUEEN{'d'};
    constexpr char BLACK_QUEEN{'D'};

    constexpr char WHITE_TOWER{'t'};
    constexpr char BLACK_TOWER{'T'};

    constexpr char WHITE_KING{'r'};
    constexpr char BLACK_KING{'R'};

    constexpr char WHITE_PAW{'p'};
    constexpr char BLACK_PAW{'P'};

    /**
     * @brief This class implements a chessboard
     *
     */
    class Chessboard
    {
    public:
        /**
         * @brief Construct a new Chessboard
         *
         */
        Chessboard();

        /**
         *@brief Set the cell [c.y][c.x] with p, reset limbo with p and set respawn_place to c
         *
         *@param c the cell of the matrix we want to set
         *@param p  the pointer to the Piece we want to set
         */
        void set_piece(const Coordinates &c, Piece *p);

        /**
         *@brief This function returns the pointer to the piece in [c.y][c.x]
         *
         *@param c the cell of the matrix we want to ispectionate
         *
         *@return  a pointer to the Piece in v(x,y)
         *@return  nullptr if there's no Piece* in that cell
         *
         */
        Piece *get_piece(const Coordinates &c) const
        {
            return v[c.y][c.x].get();
        }

        /**
         *
         *@brief This function create a snapshot of the state of the chessboard
         *
         *@return string of the state
         */
        std::string snapshot() const;

        /**
         * @brief Swap the content of a cell at [from.y][from.x] and [to.y][to.x]
         *
         * @param from Coordinates of first piece
         *
         * @param to  Coordinates of second piece
         */
        void swap_positions(const Coordinates &from, const Coordinates &to);

        /**
         * @brief Undo the last setPiece(). Be careful when you use it!
         */
        void restore_setPiece()
        {
            this->v[this->respawn_point.y][this->respawn_point.x].reset(limbo.release());
        }

        /**
         * @brief Incapsulate the creation of the piece we want to promote
         *
         * @param taget_index the charachter of the piece
         * @param coord the coordinates where the paw get promoted
         */
        void promote(char target_index, const Coordinates &coord);
        /**
         * @brief Assignment operator disabled
         */
        Chessboard &operator=(const Chessboard &) = delete;

    private:
        /**
         * @brief This variable implements the matrix: chessgame::Chesboard guarantees an incapsulation of this bidimensional array
         *
         */
        std::unique_ptr<Piece> v[ROWS][COLUMNS];

        /**
         * @brief Limbo is the variable which owns a Piece* when it is removed from the chessboard: we want to implement the posibility of restore the remotion
         *
         */
        std::unique_ptr<Piece> limbo;

        /**
         * @brief This Coordinates represents the cell where the Piece* owned by limbo was before the remotion
         *
         */
        Coordinates respawn_point;
    };
    /**
     * @brief Helper function: checks if coordinates are out of bounds
     *
     * @param coord coordinates we want to check
     *
     * @throw std::invalid_argument if coordinates are out of range
     */
    void check_coordinates(const Coordinates &coord);
}

#endif