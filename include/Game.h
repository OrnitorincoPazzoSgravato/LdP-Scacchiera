/**
 * @file Game.h
 * @author Riccardo Zuech
 * @brief This class represents a game of chess. It only has one public method, play(), used to start the game. An istance of Game can be used to play one and only one game,
 * to play more other istances of Game must be created. 
 * @version 0.1
 * @date 2022-01-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef GAME_H
#define GAME_H

#include <fstream>

#include "./chessgame/Chessboard.h"
#include "./chessgame/Player.h"
#include "./chessgame/Utilities.h"

namespace gameplay
{
	/**
	 * @brief manages the special rule "arrocco", returns if the provided move is a case of "arrocco"
	 * 
	 * @param move array of two coordinates representing move
	 * @param board const reference to the currently used board
	 * @return true 
	 * @return false 
	 */
	bool isArrocco(const std::array<chessgame::Coordinates, 2> &move, const chessgame::Chessboard& board);
	/**
	 * @brief classe che rappresenta una partita a scacchi.
	 * Deve occuparsi dell'inizializzazione della partita, dello svolgimento dei turni,
	 * del controllo della validità delle mosse e dell'applicazione delle regole speciali.
	 * Inoltre deve produrre un file di log di riepilogo delle mosse.
	 */
	class Game
	{
		chessgame::Chessboard board;
		/**
		 * @brief Number of moves executed in the current istance of Game.
		 */
		int n_moves;
		/**
		 * @brief True if p1's turn, false if p2's turn.
		 */
		bool current_turn;
		bool is_bot_game;
		/**
		 * @brief Pointers to the two players.
		 */
		chessgame::Player *p1, *p2;
		/**
		 * @brief coordinates to the two player's kings. Used to speed up methods based on a king's check status.
		 */
		chessgame::Coordinates p1_king_coord, p2_king_coord; 
		std::ofstream log_file; // ofstream representing the log file of the game
		/**
		 * @brief Number of turns of stalling. Used for implementing "patta".
		 */
		int stall_counter;
		/**
		 * @brief Pointer to an istance of Coordinates representing the position of the last en_passant - elegible paw. Used a pointer as nullptr is a valid
		 * value for the rule implementation (no paw moved by two tiles on the previous turn).
		 */
		chessgame::Coordinates *en_passante_coord;

		/**
		 * @brief Returns an array of both possible PieceColor's values in a randomic order.
		 * 
		 * @return std::array<chessgame::PieceColor&, 2> 
		 */
		std::array<chessgame::PieceColor, 2> getRandColors();
		/**
		 * @brief Writes a move to the game's log file.
		 * 
		 * @param move move to be recorded in the log
		 */
		void writeLog(const std::string &move);
		/**
		 * @brief Checks if the current player's king is checked.
		 * 
		 * @return true 
		 * @return false 
		 */
		bool isPlayerKingInCheck();
		/**
		 * @brief Checks if the current player's king is checked.
		 * @note Used to check if a move is an istance of self-checking-
		 * 
         * @param king_coord coordinates of the current player's king.
		 * @return true 
		 * @return false 
		 */
		bool isPlayerKingInCheck(const chessgame::Coordinates& king_coord);
		/**
         * @brief Checks if the provided move is valid and executes it.
		 * 
		 * @return true 
		 * @return false 
         */
		bool playerMove(std::array<chessgame::Coordinates, 2> &move);
		/**
		 * @brief Checks if the piece at the provided coordinates is promotable and proceeds to promote it.
		 * 
		 * @param coord coordinate of the piece to check
		 * @return char representing the promoted piece, null character if the promotion didn't happen
		 */
		char promotion(const chessgame::Coordinates &coord);
		/**
		 * @brief Updates the has_already_moved attribute of paws, king and towers
		 * 
		 * @param coord the coordinate of the piece that's about to move
		 */
		void updateFirstMove(const chessgame::Coordinates &coord);
		/**
		 * @brief Function to be called when a successful move has been recognized. Used to call and apply methods and algorithms for correctly ending a turn.
		 * 
		 * @param move the array representation of the move
		 * @param is_swap disables the capture flag if true
		 * @return std::string representation of the legal move (to be logged in the log file)
		 */
		std::string legalTurnCleanUp(const std::array<chessgame::Coordinates, 2> &move, bool is_swap);
		/**
		 * @brief Checks if the provided move is a case of a paw's two-tiles movement.
		 * 
		 * @param move the array representation of the move
		 * @return true 
		 * @return false 
		 */
		bool isPawTwoTilesMovement(const std::array<chessgame::Coordinates, 2> &move);
		/**
		 * @brief Checks if the provided move is a case of special rule "en passant".
		 * 
		 * @param piece_symbol symbol of the moving piece
		 * @param to target coordinate of the provided piexe
		 * @return true 
		 * @return false 
		 */
		bool isEnPassant(char piece_symbol, const chessgame::Coordinates &to);
		/**
		 * @brief Checks if the provided piece can move from and to the provided coordinates.
		 * 
		 * @param p piece about to move
		 * @param from starting coordinate
		 * @param to ending coordinate
		 * @return true 
		 * @return false 
		 */
		bool isDefaultMove(chessgame::Piece &p, const chessgame::Coordinates &from, const chessgame::Coordinates &to);
		/**
		 * @brief Checks the current state of the game to see if the game has ended/should end.
		 * If it's a full bot game, then it always ends in certain amount of moves declared in kBot_moves.
		 * 
		 * @return true if game over
		 * @return false if game can continue
		 */
		bool isGameOver();
		/**
		 * @brief Checks if the provided move (from - to), for the specified piece, ends up in a case of self-checking.
		 * 
		 * @param from coordinate to move from
		 * @param to coordinate to move to
		 * @param piece_symbol symbol representing the peice to move
		 * @param is_capture self-explanatory flag
		 * @param is_arrocco self-explanatory flag
		 * @return true 
		 * @return false 
		 */
		bool isMoveSelfCheck(const chessgame::Coordinates& from, const chessgame::Coordinates& to, char piece_symbol, bool is_capture, bool is_arrocco);

		/**
		 * @brief Get the Current Player object
		 * 
		 * @return chessgame::Player*
		 */
		chessgame::Player* getCurrentPlayer() {
			return this->current_turn ? this->p1 : this->p2;
		}
		/**
		 * @brief Get the Current Player King coordinates
		 * 
		 * @return chessgame::Coordinates 
		 */
		chessgame::Coordinates getCurrentPlayerKing() {
			return this->current_turn ? this->p1_king_coord : this->p2_king_coord; 
		}
		/**
		 * @brief Set the Current Player King coordinates
		 * 
		 * @param coord 
		 */
		void setCurrentPlayerKing(const chessgame::Coordinates& coord) {
			this->current_turn ? this->p1_king_coord = coord : this->p2_king_coord = coord;
		}

		/**
		 * @brief Get all possible moves for a specifies piece based on the board's current state. Except for king in tower arrocco, as it's already covered by tower in king
		 * arrocco.
		 * @note In the current implementation, this method is used on in isGameOver() to check if a checked opponent still has move available to uncheck their king. Obviously,
		 * if tower in king arrocco exist, then also king in tower exists, so it's not needed to add complexity to the algorithm by adding its calculation. Nonetheless the
		 * algorithm is still coded, but it has been commented out.
		 * 
		 * @param piece_coord
		 * @return std::vector<chessgame::Coordinates> vector containing all the coordinates the piece can move to
		 */
		std::vector<chessgame::Coordinates> getPieceMovesAll(const chessgame::Coordinates &piece_coord);

	public:
		/**
		 * @brief A full bot game is considered invalid after this number of moves without a winner
		 * 
		 */
		static const int kBot_moves = 500;
		/**
		 * @brief Constructs a new Game object and initialize one human player and one bot player
		 * 
		 */
		Game();
		/**
		 * @brief Constructs a new Game object, and initialize its players based on the argument's value
		 * 
		 * @param is_bot_game false: 1 bot and 1 human; true: 2 bots
		 */
		Game(bool is_bot_game);
		
		// We don't want to have a copy of an ongoing game.
		Game(const Game&) = delete;
		Game& operator=(const Game&) = delete;

		/**
		 * @brief starts a game of chess, logging valid moves in "game_log.txt"
		 * 
		 */
		void play();

		/**
		 * @brief Destroy the Game object and closes the log_file if not already closed
		 * 
		 */
		~Game();
	};
};

#endif