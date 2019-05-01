#include "Game.hpp"
#include "../states/LevelEditorGameState.hpp"

Game::Game()
{
	register_game_state<GameStates::LevelEditor>();
	switch_to_game_state<GameStates::LevelEditor>();
}

template <Game::GameStates gameState>
void Game::switch_to_game_state()
{
	currentGameState_ = gameStates_[gameState];
}

template <Game::GameStates gameState>
void Game::register_game_state()
{
	switch (gameState)
	{
	case GameStates::LevelEditor:
		gameStates_[gameState] = std::make_unique<LevelEditorGameState>(LevelEditorGameState{});
		break;
	default:
		break;
	}
}

int Game::loop()
{
	while (running_)
	{
		sf::Clock clock{};

		while (window_.isOpen())
		{
			const auto dt = clock.restart().asSeconds();

			currentGameState_->handle_input(window_, dt);
			currentGameState_->update(window_, dt);

			currentGameState_->clear(window_);
			currentGameState_->draw(window_, dt);

			window_.display();
		}
	}

	return EXIT_SUCCESS;
}
