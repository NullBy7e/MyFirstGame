#pragma once

#include <SFML/Graphics.hpp>

#include "entity.hpp"
#include "entity_health_bar.hpp"
#include "entity_type.hpp"

class Boss : public Entity
{
public:
	Boss(sf::Sprite& sprite) : Entity(sprite, ENTITY_TYPE::BOSS)
	{
		this->max_health = 500;
		this->current_health = 500;
	}

	void repositionUi(const int width, const int height)
	{
		auto pos = this->getSprite().getPosition();
		auto health_bar_pos_x = pos.x - this->getSprite().getLocalBounds().width;
		auto health_bar_pos_y = pos.y - this->getSprite().getLocalBounds().height;
		this->health_bar.setPosition(sf::Vector2f(health_bar_pos_x, health_bar_pos_y));
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

	EntityHealthBar health_bar = EntityHealthBar(200, 40);
};