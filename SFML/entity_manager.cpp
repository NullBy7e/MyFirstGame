#include "entity_manager.hpp"

EntityManager::EntityManager()
{
}

EntityManager::~EntityManager()
{
	/*std::for_each(this->entities.begin(), this->entities.end(), [&](const std::pair<std::string, Entity>& ref) {
		delete &ref.second;
	});*/
}

Player& EntityManager::GetPlayer()
{
	auto player = this->entities["player"];
	return (Player&)(*player);
}

void EntityManager::CreateEntity(std::string entity_name, ENTITY_TYPE entity_type, sf::Sprite entity_sprite)
{
	switch (entity_type)
	{
	case ENTITY_TYPE::PLAYER:
	{
		Entity* entity = new Player(entity_sprite);
		this->entities[entity_name] = entity;

		break;
	}
	default:
	{
		Entity* entity = new Enemy(entity_sprite);
		this->entities[entity_name] = entity;

		break;
	}
	}
}