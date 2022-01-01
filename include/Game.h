#ifndef GAME
#define GAME

/**
 * @author Riccardo Zuech
 * @details TBD
 * 
*/

#include <Chessboard.h>
#include <Player.h>

namespace game {
	/**
	 * @brief classe che rappresenta lo svolgimento di una partita a scacchi.
	 * Deve occuparsi dell'inizializzazione della partita, dello svolgimento dei turni,
	 * del controllo della validià delle mosse e dell'applicazione delle regole speciali.
	 * Inoltre deve produrre un file di log di riepilogo delle mosse
	 */
	class Game {
		chessgame::Chessboard board;
		int n_moves;
		public:
			Game();
			/**
			 * @brief Construct a new Game object, and initialize its players based on the argument's value
			 * 
			 * @param is_bot_game false: 1 bot and 1 human; true: 2 bots
			 */
			Game(bool is_bot_game);
			void play();
	};
};

#endif GAME