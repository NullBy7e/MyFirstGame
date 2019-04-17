#include "window.h"

Window::Window()
{
}

Window::~Window()
{
}

void Window::HandleInput()
{
	sf::Event event;

	while (this->pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
		{
			this->close();
			break;
		}
		}
	}
}