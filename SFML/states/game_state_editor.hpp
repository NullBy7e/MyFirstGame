#pragma once

#include <SFML/Graphics.hpp>

#include "../tmx/tmx_parser.hpp"
#include "../states/game_state.hpp"

#include "../core/map.hpp"

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