#pragma once

#include <SFML/Graphics.hpp>

#include "player.hpp"
#include "enemy.hpp"
#include "entity_type.hpp"

class EntityManager
{
public:
	EntityManager();
	~EntityManager();

	Player& GetPlayer();

	void CreateEntity(std::string entity_name, ENTITY_TYPE entity_type, sf::Sprite entity_sprite);

private:

	std::map<std::string, Entity*> entities;
};