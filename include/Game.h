#ifndef GAME
#define GAME

/**
 * @author Riccardo Zuech
 * @details TBD
 * 
*/

#include <Chessboard.h>
#include <Player.h>

#include <fstream>

namespace chessgame {
	/**
	 * @brief classe che rappresenta lo svolgimento di una partita a scacchi.
	 * Deve occuparsi dell'inizializzazione della partita, dello svolgimento dei turni,
	 * del controllo della validià delle mosse e dell'applicazione delle regole speciali.
	 * Inoltre deve produrre un file di log di riepilogo delle mosse
	 */
	class Game {
		chessgame::Chessboard board;
		int n_moves;
		std::unique_ptr<chessgame::Player> p1, p2;
		std::ofstream log_file;

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
		 * @brief checks the current state of the game to see if the game has ended
		 * 
		 * @return true if game over
		 * @return false if game can continue
		 */
		bool isGameOver();

		public:
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