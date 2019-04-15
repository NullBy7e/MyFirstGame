#pragma once

#include "entity.hpp"
#include "entity_health_bar.hpp"

class Player : public Entity
{
public:
	Player(int id, std::string name, sf::Sprite sprite, Dexode::EventBus* eventbus);

	void repositionUi(const int width, const int height);
	void inflictDamage(int health_damage);

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	EntityHealthBar health_bar = EntityHealthBar(100, 20);
};