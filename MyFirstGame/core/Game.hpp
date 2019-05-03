#pragma once

#include <memory>
#include <vector>

#include "../states/GameState.hpp"
#include "Window.hpp"

/**
 * \brief the core Game class
 */
class Game
{
public:
	Game();

	/**
	 * \brief the main game loop, runs indefinitely.
	 * \return EXIT_SUCCESS or EXIT_FAILURE
	 */
	int loop();
private:

	enum class GameStates
	{
		LevelEditor
	};

	void switch_to_game_state(GameStates game_state);
	void register_game_state(GameStates game_state);

	/**
	 * \brief The main window of the game.
	 */
	Window window_;

	/**
	 * \brief map of available game states.
	 */
	std::map<GameStates, std::shared_ptr<GameState>> gameStates_;

	/**
	 * \brief the current game state that's active.
	 */
	std::shared_ptr<GameState> currentGameState_;

	/**
	 * \brief indicates whether the game is running.
	 */
	bool running_{true};
};
