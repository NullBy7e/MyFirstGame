#pragma once

#include <SFML/Graphics.hpp>

#include "tmx_parser.hpp"
#include "game_state.hpp"

#include "map.hpp"
#include "map_tile_layer.hpp"
#include "map_object_layer.hpp"
#include "map_object.hpp"
#include "map_object_property.hpp"

class GameStateEditor : public GameState
{
private:

	sf::View gameView;
	sf::View guiView;

	Map * map;
public:

	virtual void draw(const float dt);
	virtual void update(const float dt);
	virtual void handleInput();

	GameStateEditor(Game* game);
	~GameStateEditor();
};