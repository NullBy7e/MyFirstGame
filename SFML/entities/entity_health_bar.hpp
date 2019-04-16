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

#pragma once

#include <SFML/Graphics.hpp>

class EntityHealthBar : public sf::Drawable
{
public:
	EntityHealthBar(float width, float height)
	{
		this->health_bar_outer.setSize(sf::Vector2f(width, height));

		this->health_bar_outer.setFillColor(sf::Color::Yellow);
		this->health_bar_outer.setOutlineColor(sf::Color::Yellow);
		this->health_bar_outer.setOutlineThickness(1.0f);

		this->health_bar_inner.setSize(sf::Vector2f(width, height));
		this->health_bar_inner.setFillColor(sf::Color::Red);
	}

	void setHealthPercentage(int health_percentage)
	{
		this->health_bar_inner.setSize(sf::Vector2f(health_percentage, this->health_bar_inner.getSize().y));
	}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(health_bar_outer, states);
		target.draw(health_bar_inner, states);
	}

	void setPosition(sf::Vector2f position)
	{
		health_bar_outer.setPosition(position);
		health_bar_inner.setPosition(position);
	}

	sf::RectangleShape health_bar_outer;
	sf::RectangleShape health_bar_inner;

private:
};