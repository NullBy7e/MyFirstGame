#include "Window.hpp"
#include <imgui-SFML.h>
#include <imgui.h>

Window::Window()
{
	window_.create(sf::VideoMode(1280, 1024), "MyFirstGame", sf::Style::None);
	window_.setFramerateLimit(60);
}

void Window::display()
{
	window_.display();
}

bool Window::poll_event(sf::Event& event)
{
	const auto e = window_.pollEvent(event);

	if (e)
	{
		if (event.type == sf::Event::Closed)
		{
			window_.close();
		}
	}

	dt_ = clock_.restart();

	return e;
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
}

sf::RenderWindow& Window::get()
{
	return window_;
}
