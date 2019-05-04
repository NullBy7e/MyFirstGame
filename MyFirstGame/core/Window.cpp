#include "Window.hpp"

Window::Window()
{
	window_.create(sf::VideoMode(1280, 1024), "MyFirstGame", sf::Style::Titlebar | sf::Style::Close);
	window_.setFramerateLimit(60);
}

void Window::display()
{
	dt_ = clock_.restart().asSeconds();
	window_.display();
}

bool Window::poll_event(sf::Event& event)
{
	return window_.pollEvent(event);
}

void Window::clear()
{
	window_.clear(sf::Color::Black);
}

void Window::draw(sf::Drawable& drawable)
{
	window_.draw(drawable);
}

bool Window::is_open() const
{
	return window_.isOpen();
;}
