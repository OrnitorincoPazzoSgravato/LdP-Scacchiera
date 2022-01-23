/**
 * @file Bot.cpp
 * @author Enrico Cavinato
 * @brief
 * @version 0.1
 * @date 2022-01-13
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <array>
#include <vector>
#include <ctime>
#include <random>

#include "../../include/chessgame/Bot.h"
#include "../../include/chessgame/Chessboard.h"
#include "../../include/chessgame/Player.h"
#include "../../include/chessgame/Regina.h"
#include "../../include/chessgame/Utilities.h"

namespace chessgame
{
    Coordinates next_cell(const Coordinates &coord)
    {
        //  row ++
        int x {coord.x}, y {coord.y + 1};

        // if end of column, next row
        if (y == ROWS)
        {
            // a caporiga
            y = 0;
            // next column
            x++;
        }
        // if end of matrix
        if (x == COLUMNS)
        {
            // start from the beginning of the matrix
            y = 0;
            x = 0;
        }
        return Coordinates(x, y);
    }


    std::array<Coordinates, 2> Bot::think()
    {
        int count{0};
        // generate coordinates
        Coordinates from = this->starting_tile;

        // while we ispectionate
        while (count < CELLS)
        {
            
            count++;
            // get piece in from, if empty cell continue
            Piece *p{this->board.get_piece(from)};
            if (!p) {
                from = next_cell(from);
                continue;
            }

            PieceColor p_color = p->getColor();
            // if a piece does exist and is controlled by this player
            if (p_color == this->pieceColor)
            {
                starting_tile = from;
                // get possible moves
                std::vector<Coordinates> possible_moves{p->getMoves(this->board, from)};

                char p_symbol = p->getSymbol();
                bool p_is_paw = p_symbol == chessgame::WHITE_PAW || p_symbol == chessgame::BLACK_PAW;
                bool p_is_tower = p_symbol == chessgame::WHITE_TOWER || p_symbol == chessgame::BLACK_TOWER;

                if(p_is_paw && !dynamic_cast<Pedone*>(p)->has_already_moved) {
                    int offset = p_color == WHITE ? 2 : -2;
                    if((p_color == WHITE && from.y != 6) || (p_color == BLACK && from.y != 1)) possible_moves.push_back(Coordinates{from.x, from.y + offset});
                }
                else if(p_is_paw) {
                    int offset = p_color == WHITE ? 1 : -1;
                    if(from.x != (COLUMNS - 1)) possible_moves.push_back(Coordinates{from.x + 1, from.y + offset});
                    else if(from.x != 0) possible_moves.push_back(Coordinates{from.x - 1, from.y + offset});
                }
                else if(p_is_tower && !dynamic_cast<Torre*>(p)->has_already_moved) {
                    int i = from.x;
                    while(0 <= i && i < COLUMNS) {
                        Piece* obstacle_p = this->board.get_piece(Coordinates{i, from.y});
                        if(!obstacle_p) {
                            if(from.x == COLUMNS - 1) i--;
                            else i++;
                            continue;
                        }
                        if(obstacle_p->getColor() != p_color) break;
                        bool obstacle_is_king = obstacle_p->getSymbol() == chessgame::WHITE_KING || obstacle_p->getSymbol() == chessgame::BLACK_KING;
                        if(obstacle_is_king && !dynamic_cast<Re*>(obstacle_p)->has_already_moved) {
                            possible_moves.push_back(Coordinates{i, from.y});
                            break;
                        }
                        else break;
                        if(from.x == COLUMNS - 1) i--;
                        else i++;
                    }
                }
                

                // if a possible move does exist
                size_t moves_number{possible_moves.size()};
                
                if (moves_number != 0)
                {
                    if(last_move_index < 0) last_move_index = std::rand() % moves_number;

                    int index = this->last_move_index >= moves_number ? 0 : last_move_index;
                    this->last_move_index = index + 1;
                    this->moves_used++;

                    if(moves_used > moves_number) {
                        this->moves_used = 0;
                        this->last_move_index = -1;
                        starting_tile = next_cell(from);
                    }

                    // returns a move
                    Coordinates to{possible_moves[index]};
                    return std::array<Coordinates, 2>{from, to};
                }

            }
            
            from = next_cell(from);
        }
        // good practice : this function has a defualt move to return: it never occurs because 
        // gameplay::Game controls checkmate
        return std::array<Coordinates,2> {Coordinates {-1,-1},Coordinates {-1,-1}};
    }

    char Bot::getPromotionTarget()
    {
        if (this->pieceColor == WHITE)
            return WHITE_QUEEN;
        else
            return BLACK_QUEEN;
    }
}