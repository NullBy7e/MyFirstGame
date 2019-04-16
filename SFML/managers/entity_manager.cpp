#include "entity_manager.hpp"

EntityManager::EntityManager(Dexode::EventBus* eventbus)
{
	this->eventbus = eventbus;
}

EntityManager::~EntityManager()
{
	for (std::map<int, Entity*>::iterator it = this->entities.begin(); it != this->entities.end(); ++it)
	{
		delete it->second;
	}
}

Entity* EntityManager::getEntity(int entity_id)
{
	for (std::map<int, Entity*>::iterator it = this->entities.begin(); it != this->entities.end(); ++it)
	{
		if (it->second->id == entity_id)
		{
			return this->entities[it->second->id];
		}
	}
}

Entity* EntityManager::getEntity(std::string entity_name)
{
	for (std::map<int, Entity*>::iterator it = this->entities.begin(); it != this->entities.end(); ++it)
	{
		if (it->second->name == entity_name)
		{
			return this->entities[it->second->id];
		}
	}
}

std::vector<Entity*> EntityManager::getEntities(ENTITY_TYPE entity_type)
{
	std::vector<Entity*> entities;

	for (std::map<int, Entity*>::iterator it = this->entities.begin(); it != this->entities.end(); ++it)
	{
		if (it->second->type == entity_type)
		{
			entities.push_back(it->second);
		}
	}

	return entities;
}

void EntityManager::createEntity(int entity_id, std::string entity_name, ENTITY_TYPE entity_type, sf::Sprite entity_sprite)
{
	switch (entity_type)
	{
	default:
	{
		this->entities[entity_id] = new Enemy(entity_id, entity_name, entity_sprite, this->eventbus);
		this->entities[entity_id]->name = std::string(entity_name);
		break;
	}
	}
}