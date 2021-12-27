/*

    @author: Enrico Cavinato
    @date: 2021-12-27

    This class represents a chessboard

*/

#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include<string>
#include<vector>
#include "Utilities.h"
#include "Piece.h"

namespace chessgame

{

class Chessboard {
private: 
    std::vector<std::vector<Piece>> v ;
public:
    //costruttore di default, inizializza la scacchiera
    Chessboard();
    
    //costruttore di copia non necessario ( bisogno di una sola scacchiera per partita)
    //costruttore di assegnamento non necessario (vedi sopra)
    
    //inserisce un pezzo senza controllarne la validità ( compito di game )
    void set_piece(const Coordinates, const Piece& p);
    Piece* get_piece(const Coordinates);
    std::string& snapshot();
};
}

#endif 