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

#include "player.hpp"

Player::Player(int id, std::string name, sf::Sprite sprite, Dexode::EventBus* eventbus) : Entity(id, name, sprite, ENTITY_TYPE::PLAYER, eventbus)
{
	this->move_speed = 20;
	this->max_health = 200;
	this->current_health = 200;
}

void Player::repositionUi(const int width, const int height)
{
	this->health_bar.setPosition(sf::Vector2f(50, 50));
}

void Player::inflictDamage(int health_damage)
{
	Entity::inflictDamage(health_damage);

	/* update health bar */
	this->health_bar.setHealthPercentage(this->getHealthPercentage());
}

void Player::updateOVH()
{
	this->health_bar.setPosition(
		sf::Vector2f(this->getSprite().getPosition().x - this->getSprite().getLocalBounds().width,
			this->getSprite().getPosition().y - this->getSprite().getLocalBounds().height + 25)
	);
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite, states);
	target.draw(health_bar, states);
}