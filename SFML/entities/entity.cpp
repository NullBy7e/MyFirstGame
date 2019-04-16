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

#include "entity.hpp"

Entity::Entity(int id, std::string name, sf::Sprite sprite, ENTITY_TYPE type, Dexode::EventBus* eventbus)
{
	id = int(id);
	name = std::string(name);

	this->sprite = sf::Sprite(sprite);
	this->type = type;

	this->eventbus = eventbus;
}

Entity::~Entity()
{
}

sf::Sprite& Entity::getSprite()
{
	return sprite;
}

void Entity::move(sf::Vector2f offset)
{
	this->eventbus->notify(Events::EntityMoveEvent{ offset.x, offset.y, this });
}

void Entity::domove(sf::Vector2f offset)
{
	this->sprite.move(offset);
}

void Entity::setPosition(sf::Vector2f position)
{
	sprite.setPosition(position);
}

void Entity::inflictDamage(int health_damage)
{
	current_health -= health_damage;

	if (current_health <= 0)
	{
		is_dead = true;
		current_health = 0;
	}
}

void Entity::update(float x, float y)
{
	this->move(sf::Vector2f(x, y));
}

void Entity::move(int move_action)
{
	move((MOVE_ACTION)(move_action));
}

void Entity::move(MOVE_ACTION move_action)
{
	float x = 0;
	float y = 0;

	switch (move_action)
	{
	case MOVE_ACTION::LEFT:
	{
		x -= this->move_speed;
		break;
	}
	case MOVE_ACTION::RIGHT:
	{
		x += this->move_speed;
		break;
	}
	case MOVE_ACTION::UP:
	{
		y -= this->move_speed;
		break;
	}
	case MOVE_ACTION::DOWN:
	{
		y += this->move_speed;
		break;
	}

	default: break;
	}

	this->update(x, y);
}

int Entity::getHealthPercentage()
{
	if (current_health == 0)
		return 0;

	return (int)(current_health * 100.0 / max_health);
}