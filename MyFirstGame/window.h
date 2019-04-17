#pragma once

#include <SFML/Graphics.hpp>

class Window : public sf::RenderWindow
{
public:
	Window();
	~Window();

	void HandleInput();
};
