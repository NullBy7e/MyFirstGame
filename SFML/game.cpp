#include <stack>
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "game.hpp"
#include "game_state.hpp"
#include "texture_manager.hpp"

void Game::pushState(GameState* state)
{
	this->states.push(state);

	return;
}

void Game::popState()
{
	delete this->states.top();
	this->states.pop();

	return;
}

void Game::changeState(GameState* state)
{
	if (!this->states.empty())
		popState();
	pushState(state);

	return;
}

GameState* Game::peekState()
{
	if (this->states.empty()) return nullptr;
	return this->states.top();
}

void Game::gameLoop()
{
	bool editorToggled;
	sf::Clock clock;

	while (this->window.isOpen())
	{
		sf::Time elapsed = clock.restart();
		float dt = elapsed.asSeconds();

		if (peekState() == nullptr)
			continue;

		peekState()->handleInput();
		peekState()->update(dt);

		this->window.clear(sf::Color::Black);

		if (peekState()->mapEditorOpened)
		{
			editorToggled = true;
		}
		else
		{
			editorToggled = false;
			peekState()->draw(dt);
		}

		this->window.display();
	}
}

void Game::loadTextures()
{
	texmgr.loadTexture("background", "textures/background.png");
	texmgr.loadTexture("player", "textures/sprites/player/knight_f_run_anim_f1.png");
}

void Game::loadEntities()
{
	this->entmgr.CreateEntity("player", ENTITY_TYPE::PLAYER, sf::Sprite(texmgr.getRef("player")));
}

Game::Game()
{
	this->loadTextures();
	this->loadEntities();

	this->window.create(sf::VideoMode(1280, 1024), "SFML", sf::Style::Titlebar | sf::Style::Close);
	this->window.setFramerateLimit(60);

	this->background.setTexture(this->texmgr.getRef("background"));
}

Game::~Game()
{
	while (!this->states.empty())
		popState();
}