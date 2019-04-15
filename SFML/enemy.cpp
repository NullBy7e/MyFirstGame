#include "enemy.hpp"

Enemy::Enemy(int id, std::string name, sf::Sprite sprite, Dexode::EventBus* eventbus) : Entity(id, name, sprite, ENTITY_TYPE::ENEMY, eventbus)
{
	this->max_health = 100;
	this->current_health = 100;
}

void Enemy::inflictDamage(int health_damage)
{
	Entity::inflictDamage(health_damage);

	/* update health bar */
	this->health_bar.setHealthPercentage(this->getHealthPercentage());
}

void Enemy::update(float x, float y)
{
	Entity::update(x, y);
}

void Enemy::updateOVH()
{
	this->health_bar.setPosition(
		sf::Vector2f(this->getSprite().getPosition().x + 20,
			this->getSprite().getPosition().y - this->getSprite().getLocalBounds().height + 25)
	);
}

void Enemy::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(*sprite, states);
	target.draw(health_bar, states);
}