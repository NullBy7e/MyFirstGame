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