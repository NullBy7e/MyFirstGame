#pragma once

#include <SFML/Graphics.hpp>

class Window : public sf::RenderWindow
{
public:
	Window();
	~Window();

	void HandleInput(sf::View& viewport);

	sf::Vector2f oldPos;
	bool moving = false;
};
