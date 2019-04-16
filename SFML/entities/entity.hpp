#pragma once

#include <SFML/Graphics.hpp>

#include "../enums/entity_type.hpp"
#include "../enums/move_action.hpp"

#include "../events/entity_events.hpp"
#include "../eventbus/EventBus.hpp"

class Entity : public sf::Drawable
{
public:
	Entity(int id, std::string name, sf::Sprite sprite, ENTITY_TYPE type, Dexode::EventBus* eventbus);
	~Entity();

	sf::Sprite& getSprite();

	void domove(sf::Vector2f offset);
	void move(sf::Vector2f offset);
	void setPosition(sf::Vector2f position);
	void inflictDamage(int health_damage);
	void update(float x, float y);
	void move(MOVE_ACTION move_action);
	void move(int move_action);

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

	int left_tile;
	int right_tile;
	int up_tile;
	int down_tile;

protected:
	sf::Sprite sprite;
};