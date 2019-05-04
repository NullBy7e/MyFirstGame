#include "Game.hpp"
#include "../states/LevelEditorGameState.hpp"
#include <imgui-SFML.h>

Game::Game()
{
	register_game_state(GameStates::LevelEditor);
	switch_to_game_state(GameStates::LevelEditor);
}

void Game::switch_to_game_state(const GameStates game_state)
{
	currentGameState_ = gameStates_[game_state];
}

void Game::register_game_state(const GameStates game_state)
{
	switch (game_state)
	{
	case GameStates::LevelEditor:
		gameStates_[game_state] = std::make_unique<LevelEditorGameState>(LevelEditorGameState{window_});
		break;
	default:
		break;
	}
}

int Game::loop()
{
	while (window_.is_open())
	{
		currentGameState_->handle_input();
		currentGameState_->update();

		currentGameState_->clear();
		currentGameState_->draw();

		window_.display();
	}

	ImGui::SFML::Shutdown();
	return EXIT_SUCCESS;
}
