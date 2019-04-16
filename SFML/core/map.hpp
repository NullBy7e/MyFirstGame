#pragma once

#include <string>
#include <map>
#include <vector>

#include <SFML/Graphics.hpp>

#include "../tmx/tmx_tile_layer.hpp"
#include "../tmx/tmx_object_layer.hpp"

#include "game.hpp"

class Map
{
public:
	Map() {};
	Map(Game* game);
	~Map();

	sf::Vector2u size;
	sf::Vector2u tileSize;

	std::vector<TmxTileLayer> tile_layers;
	std::vector<TmxObjectLayer> object_layers;

	std::map<int, sf::Sprite> sprites;

	bool player_spawned = false;

	/* Draw the map */
	void draw(sf::RenderWindow& window, float dt);

	/* Set the sprites to use */
	void setSprites(std::map<int, sf::Sprite>);

	void addTileLayer(TmxTileLayer layer);
	void addObjectLayer(TmxObjectLayer layer);

	void createEntities();

	EntityManager* entmgr;

	Dexode::EventBus* eventbus = new Dexode::EventBus();
private:
	Game* game;
};