/*
MIT License

Copyright (c) 2019 Youri de Mooij

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "window.hpp"

using namespace mfg::core;

void window::handleInput(sf::View& viewport)
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