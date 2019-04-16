#pragma

#include <SFML/Graphics.hpp>

#include "../events/entity_events.hpp"

#include "../entities/entity.hpp"
#include "../entities/player.hpp"
#include "../entities/enemy.hpp"

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

private:
	Dexode::EventBus* eventbus;

	std::map<int, Entity*> entities;
};