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