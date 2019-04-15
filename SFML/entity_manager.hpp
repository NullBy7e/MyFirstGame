#pragma

#include <SFML/Graphics.hpp>

#include "entity_events.hpp"

#include "entity.hpp"
#include "player.hpp"
#include "enemy.hpp"

class Map;

class EntityManager
{
public:
	EntityManager(Dexode::EventBus* mapeventbus);
	~EntityManager();

	Entity* getEntity(int entity_id);
	Entity* getEntity(std::string entity_name);
	std::vector<Entity*> getEntities(ENTITY_TYPE entity_type);
	void createEntity(int entity_id, std::string entity_name, ENTITY_TYPE entity_type, sf::Sprite entity_sprite);

	bool move(int x, int y, Entity * entity, Map * map);

private:
	Dexode::EventBus* eventbus;

	std::map<int, Entity*> entities;
};