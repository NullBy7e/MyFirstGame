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