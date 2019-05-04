#pragma once

#include <SFML/Graphics.hpp>
#include "../drawables/Grid.hpp"

class Window
{
public:
	Window();

	void display();
	bool poll_event(sf::Event& event);
	void clear();
	void draw(sf::Drawable& drawable);
	bool is_open() const;

	float dt_{};
	sf::Clock clock_{};

	sf::RenderWindow window_;
};

