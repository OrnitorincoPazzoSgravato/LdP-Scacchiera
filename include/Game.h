/**
 * @file Game.h
 * @author Riccardo Zuech
 * @brief 
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
	 * @brief classe che rappresenta lo svolgimento di una partita a scacchi.
	 * Deve occuparsi dell'inizializzazione della partita, dello svolgimento dei turni,
	 * del controllo della validità delle mosse e dell'applicazione delle regole speciali.
	 * Inoltre deve produrre un file di log di riepilogo delle mosse
	 */
	class Game
	{
		chessgame::Chessboard board;
		int n_moves;
		bool current_turn; // true if p1's turn, false if p2's turn
		chessgame::Player p1, p2;
		chessgame::Coordinates p1_king_coord, p2_king_coord;
		std::ofstream log_file;
		int stall_counter;

		chessgame::Coordinates *en_passante_coord;

		/**
		 * @brief Returns an array of both PieceColor's values in a randomic order
		 * 
		 * @return std::array<chessgame::PieceColor&, 2> 
		 */
		std::array<chessgame::PieceColor, 2> getRandColors();
		/**
		 * @brief Writes a move to the game's log file
		 * 
		 * @param move move to be recorded in the log
		 * @return bool true if the write op succedeed, fale if it failed
		 */
		void writeLog(const std::string &move);
		/**
		 * @brief checks if the current player's king is in check
		 * 
         * @param player_identifier true if p1, false is p2
		 * @return true 
		 * @return false 
		 */
		bool isPlayerKingInCheck(bool player_identifier);
		/**
         * @brief check if the provided move is valid, if yes it is executed
         * 
         */
		bool playerMove(bool player_identifier, std::array<chessgame::Coordinates, 2> &move);
		/**
		 * @brief checks if the piece at the provided coordinates is promotable. If it is proceeds to it.
		 * 
		 * @param coord coordinate of the piece to check
		 * @return char representing the promoted piece, null character if the promotion didn't happen
		 */
		char promotion(const chessgame::Coordinates &coord);
		/**
		 * @brief updates the has_already_moved attribute of a paw, king or tower
		 * 
		 * @param coord the coordinate of the piece that's about to move
		 */
		void updateFirstMove(const chessgame::Coordinates &coord);
		/**
		 * @brief Function to be called when a successful move has been recognized. It's role is to do everything that needs to be done
		 * at the end of a turn
		 * 
		 * @param move the array representation of the move
		 * @param is_swap disables the capture function if true
		 * @return std::string string representation of the move to be logged
		 */
		std::string legalTurnCleanUp(const std::array<chessgame::Coordinates, 2> &move, bool is_swap);
		/**
		 * @brief manages the two-tiles movement of a first time moving paw, return if the provided move is a case of it.
		 * 
		 * @param move 
		 * @return true 
		 * @return false 
		 */
		bool isPawTwoTilesMovement(const std::array<chessgame::Coordinates, 2> &move);
		/**
		 * @brief manages the special rule "en passant", returns if it is a case of "en passant"
		 * 
		 * @param piece_symbol 
		 * @param to 
		 * @return true 
		 * @return false 
		 */
		bool isEnPassant(char piece_symbol, const chessgame::Coordinates &to);
		/**
		 * @brief manages the special rule "arrocco", returns if the provided move is a case of "arrocco"
		 * 
		 * @param p 
		 * @param dest_p 
		 * @return true 
		 * @return false 
		 */
		bool isArrocco(const std::array<chessgame::Coordinates, 2> &move);
		/**
		 * @brief manages base movement rules, returns if the provided piece can defaultly move to the specified tile
		 * 
		 * @param p 
		 * @param to 
		 * @return true 
		 * @return false 
		 */
		bool isDefaultMove(chessgame::Piece &p, const chessgame::Coordinates &to);
		/**
		 * @brief checks the current state of the game to see if the game has ended/should end
		 * If it's a full bot game, then it always ends in certain amount of moves declared in kBot_moves
		 * 
		 * @return true if game over
		 * @return false if game can continue
		 */
		bool isGameOver();

		bool isStalemate();

		std::vector<chessgame::Coordinates> getPieceMovesAll(const chessgame::Coordinates &piece_coord);

	public:
		/**
			 * @brief A full bot game is considered invalid after this number of moves without a winner
			 * 
			 */
		static const int kBot_moves = 100;
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