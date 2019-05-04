#include "GameState.hpp"
#include "LevelEditorGameState.hpp"
#include "../core/Window.hpp"

LevelEditorGameState::LevelEditorGameState(Window& window): GameState(window)
{
}

void LevelEditorGameState::handle_input()
{
	sf::Event event{};

	while(window_.poll_event(event))
	{
		
	}
}

void LevelEditorGameState::clear()
{
	window_.clear();
}

void LevelEditorGameState::update()
{
}

void LevelEditorGameState::draw()
{
	window_.draw(mapEditor_);
}


