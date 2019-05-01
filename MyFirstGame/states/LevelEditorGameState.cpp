#include <SFML/Graphics/Color.hpp>

#include "LevelEditorGameState.hpp"
#include "../core/Window.hpp"

void LevelEditorGameState::handle_input(Window& window, float dt)
{
	sf::Event event{};

	while(window.pollEvent(event))
	{
		
	}
}

void LevelEditorGameState::clear(Window& window)
{
	window.clear(sf::Color::Black);
}

void LevelEditorGameState::update(Window& window, float dt)
{
}

void LevelEditorGameState::draw(Window& window, float dt)
{

}


