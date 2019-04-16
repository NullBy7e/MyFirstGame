#pragma once

#include <stack>
#include <map>
#include <string>

#include <SFML/Graphics.hpp>

#include "../managers/texture_manager.hpp"
#include "../managers/entity_manager.hpp"

class GameState;

class Game
{
private:

	void loadTextures();
	void createPlayer();

public:
	std::stack<GameState*> states;

	sf::RenderWindow window;

	TextureManager texmgr;

	sf::Sprite background;

	void pushState(GameState* state);
	void popState();
	void changeState(GameState* state);
	GameState* peekState();

	void gameLoop();

	Player* getPlayer();

	Game();
	~Game();

private:
	Player* player;
};