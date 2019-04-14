#pragma once

#include <SFML/Graphics.hpp>

#include "entity_type.hpp"

class Entity : public sf::Drawable
{
public:
	Entity(sf::Sprite& sprite, ENTITY_TYPE type)
	{
		this->sprite = new sf::Sprite();
		memcpy(this->sprite, &sprite, sizeof(sprite));

		this->type = type;
	}

	virtual ~Entity()
	{
		delete sprite;
	};

	sf::Sprite& getSprite() {
		return *sprite;
	}

	virtual void setPosition(sf::Vector2f position)
	{
		sprite->setPosition(position);
	}

	virtual void inflictDamage(int health_damage)
	{
		current_health -= health_damage;

		if (current_health <= 0)
		{
			is_dead = true;
			current_health = 0;
		}
	}

	int getHealthPercentage()
	{
		if (current_health == 0)
			return 0;

		return (int)(current_health * 100.0 / max_health);
	}

	/* entity stats */
	float current_health;
	float max_health;
	float damage_per_hit;

	bool is_dead = false;

	ENTITY_TYPE type;

protected:
	sf::Sprite* sprite;
};