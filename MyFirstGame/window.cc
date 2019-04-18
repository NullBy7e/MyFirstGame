#include "window.h"

Window::Window()
{
}

Window::~Window()
{
}

void Window::HandleInput(sf::View& viewport)
{
	sf::Event event;

	float zoom = 1;
	double accumZoom = 1;

	while (this->pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
		{
			this->close();
			break;
		}
		case sf::Event::MouseButtonPressed:
			if (event.mouseButton.button == 0) {
				moving = true;
				oldPos = sf::Vector2f(sf::Mouse::getPosition(*this));
			}
			break;
		case sf::Event::MouseButtonReleased:
			moving = false;
			break;
		case sf::Event::MouseMoved:
		{
			if (!moving)
				break;

			sf::Vector2f newPos = sf::Vector2f(event.mouseMove.x, event.mouseMove.y);
			sf::Vector2f deltaPos = oldPos - newPos;

			deltaPos.x *= accumZoom;
			deltaPos.y *= accumZoom;

			viewport.move(deltaPos);
			oldPos = newPos;

			break;
		}
		case sf::Event::MouseWheelScrolled:
			if (moving)
				break;

			if (event.mouseWheelScroll.delta <= -1)
				zoom = std::min(2.f, zoom + .1f);
			else if (event.mouseWheelScroll.delta >= 1)
				zoom = std::max(.5f, zoom - .1f);

			accumZoom *= zoom;

			viewport.zoom(zoom);
			break;
		}
	}
}