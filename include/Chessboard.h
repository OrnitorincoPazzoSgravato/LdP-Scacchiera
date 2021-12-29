/*

    @author: Enrico Cavinato
    @date: 2021-12-27

    This class represents a chessboard.

*/

#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include<string>
#include<vector>
#include "Piece.h"
#include "Utilities.h"




namespace chessgame

{

constexpr int ROWS {8};
constexpr int COLUMNS {8};

class Chessboard {
private: 
    
    Piece* v[ROWS][COLUMNS];
    void initialize_black_pieces();
    void initialize_white_pieces();
    void initialize_blank_space();
public:
    Chessboard();                                           //costruttore di default, inizializza la scacchiera
    void set_piece(const Coordinates, Piece& p);      //inserisce un pezzo senza controllarne la validità ( compito di game )    
    Piece * get_piece(const Coordinates);                   // restituisce il puntatore a un pezzo che si trova nelle coordinate
    std::string& snapshot();                                // esegue lo snapshot della scacchiera
    ~Chessboard();                                          //distrut
};
}

#endif 