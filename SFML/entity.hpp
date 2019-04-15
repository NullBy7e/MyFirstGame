#pragma once

#include <SFML/Graphics.hpp>

#include "entity_type.hpp"
#include "move_action.hpp"

#include "entity_events.hpp"
#include "eventbus/EventBus.hpp"

class Entity : public sf::Drawable
{
public:
	Entity(int id, std::string name, sf::Sprite sprite, ENTITY_TYPE type, Dexode::EventBus* eventbus);
	virtual ~Entity();

	sf::Sprite& getSprite();

	virtual void domove(sf::Vector2f offset);
	virtual void move(sf::Vector2f offset);
	virtual void setPosition(sf::Vector2f position);
	virtual void inflictDamage(int health_damage);
	virtual void update(float x, float y);
	virtual void move(MOVE_ACTION move_action);
	virtual void move(int move_action);

	int getHealthPercentage();

	/* entity stats */
	float current_health;
	float max_health;
	float damage_per_hit;

	bool is_dead = false;

	ENTITY_TYPE type;

	std::string name;

	int id;

	float move_speed = 5;
	Dexode::EventBus* eventbus;

protected:
	sf::Sprite* sprite;
};