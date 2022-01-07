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

#ifndef GAME
#define GAME

#include <fstream>

#include <Chessboard.h>
#include <Player.h>

namespace gameplay {
	/**
	 * @brief classe che rappresenta lo svolgimento di una partita a scacchi.
	 * Deve occuparsi dell'inizializzazione della partita, dello svolgimento dei turni,
	 * del controllo della validità delle mosse e dell'applicazione delle regole speciali.
	 * Inoltre deve produrre un file di log di riepilogo delle mosse
	 */
	class Game {
		chessgame::Chessboard board;
		int n_moves;
		bool current_turn; // true if p1's turn, false if p2's turn
		std::unique_ptr<chessgame::Player> p1, p2;
		std::ofstream log_file;
		
		chessgame::Coordinates* en_passante_coord;

		/**
		 * @brief Returns an array of both PieceColor's values in a randomic order
		 * 
		 * @return std::array<chessgame::PieceColor&, 2> 
		 */
		std::array<chessgame::PieceColor&, 2> getRandColors();
		/**
		 * @brief Writes a move to the game's log file
		 * 
		 * @param move move to be recorded in the log
		 * @return bool true if the write op succedeed, fale if it failed
		 */
		bool writeLog(const std::string& move);
		/**
		 * @brief checks the current state of the game to see if the game has ended/should end
		 * If it's a full bot game, then it always ends in certain amount of moves declared in kBot_moves
		 * 
		 * @return true if game over
		 * @return false if game can continue
		 */
		bool isGameOver();
		/**
		 * @brief checks if the piece at the provided coordinates is promotable. If it is proceeds to it.
		 * 
		 * @param coord coordinate of the piece to check
		 * @return char representing the promoted piece, null character if the promotion didn't happen
		 */
		char promotion(const chessgame::Coordinates& coord);
		
		/**
		 * @brief Function to be called when a successful move has been recognized. It's role is to do everything that needs to be done
		 * at the end of a turn
		 * 
		 * @param p the piece moved
		 * @param move the array representation of the move, where (?)
		 * @return std::string the move to be logged
		 */
		std::string legalTurnCleanUp(std::array<chessgame::Coordinates, 2> move, chessgame::Piece& p);
		/**
		 * @brief special overloading of legalTurnCleanUp that implements a swap between pieces (used for special rule "arrocco")
		 * 
		 * @param move the array representation of the move, where (?)
		 * @param p_coord1 the first piece to swap
		 * @param p_coord2 the second piece to swap
		 * @return std::string the move to be logged
		 */
		std::string legalTurnCleanUp(std::array<chessgame::Coordinates, 2> move, chessgame::Piece& p_coord1, chessgame::Piece* p_coord2);
		/**
		 * @brief updates the has_already_moved attribute of a paw, king or tower
		 * 
		 * @param p the piece to update, it can be a nullptr
		 */
		void updateFirstMove(chessgame::Piece* p);

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

#endif GAME