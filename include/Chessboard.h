/*

    @author: Enrico Cavinato
    @date: 2021-12-27

    This class represents a chessboard.

*/
#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include<string>
#include "Piece.h"
#include "Utilities.h"
#include "../include/Alfiere.h"
#include "../include/Cavallo.h"
#include "../include/Pedone.h"
#include "../include/Re.h"
#include "../include/Regina.h"
#include "../include/Pedone.h"
#include "../include/Torre.h"
#include <string>
#include "../include/Utilities.h"
#include "../include/Piece.h"
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
    Chessboard();                                           //costruttore di default, inizializza la scacchiera
    void set_piece(const Coordinates&, Piece * );        //inserisce un pezzo senza controllarne la validità ( compito di game )    
    Piece * get_piece(const Coordinates&);                  // restituisce il puntatore a un pezzo che si trova nelle coordinate
    std::string& snapshot();                                // esegue lo snapshot della scacchiera
};
}

#endif 