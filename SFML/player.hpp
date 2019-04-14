#pragma once

#include <SFML/Graphics.hpp>

#include "entity.hpp"
#include "entity_health_bar.hpp"
#include "entity_type.hpp"

class Player : public Entity
{
public:
	Player(sf::Sprite& sprite) : Entity(sprite, ENTITY_TYPE::PLAYER)
	{
		this->max_health = 200;
		this->current_health = 200;
	}

	void repositionUi(const int width, const int height)
	{
		this->health_bar.setPosition(sf::Vector2f(50, 50));
	}

	void inflictDamage(int health_damage)
	{
		Entity::inflictDamage(health_damage);

		/* update health bar */
		this->health_bar.setHealthPercentage(this->getHealthPercentage());
	}

private:

	void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(*sprite, states);
		target.draw(health_bar, states);
	}

	EntityHealthBar health_bar = EntityHealthBar(100, 20);
};