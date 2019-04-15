#pragma once

#include <SFML/Graphics.hpp>

#include <string>
#include <map>
#include <vector>

#include "game.hpp"

#include "map_tile_layer.hpp"
#include "map_object_layer.hpp"

class Map
{
public:
	Map() {};
	Map(Game* game);
	~Map();

	sf::Vector2u size;
	sf::Vector2u tileSize;

	std::vector<MapTileLayer> tile_layers;
	std::vector<MapObjectLayer> object_layers;

	std::map<int, sf::Sprite> sprites;

	bool player_spawned = false;

	/* Draw the map */
	void draw(sf::RenderWindow& window, float dt);

	/* Set the sprites to use */
	void setSprites(std::map<int, sf::Sprite>);

	void addTileLayer(MapTileLayer layer);

	void addObjectLayer(MapObjectLayer layer);
	void createEntities();

	bool move(int x, int y, Entity* entity);

	EntityManager* entmgr;

	Dexode::EventBus* eventbus = new Dexode::EventBus();
private:
	Game* game;
};