#include "Window.hpp"

Window::Window()
{
	create(sf::VideoMode(1280, 1024), "MyFirstGame", sf::Style::Titlebar | sf::Style::Close);
	setFramerateLimit(60);
}
