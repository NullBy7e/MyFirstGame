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