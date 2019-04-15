#pragma once

#include "entity.hpp"
#include "entity_health_bar.hpp"

class Enemy : public Entity
{
public:
	Enemy(int id, std::string name, sf::Sprite sprite, Dexode::EventBus* eventbus);

	void inflictDamage(int health_damage);
	void update(float x, float y);
	void updateOVH();
private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	EntityHealthBar health_bar = EntityHealthBar(100, 20);
};