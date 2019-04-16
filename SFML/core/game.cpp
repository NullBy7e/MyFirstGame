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

#include <stack>
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "game.hpp"
#include "../states/game_state.hpp"
#include "../managers/texture_manager.hpp"

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

void Game::createPlayer()
{
	this->player = new Player(0, "player", sf::Sprite(texmgr.getRef("player")), nullptr);
}

Player* Game::getPlayer()
{
	return this->player;
}

Game::Game()
{
	this->loadTextures();
	this->createPlayer();

	this->window.create(sf::VideoMode(1280, 1024), "SFML", sf::Style::Titlebar | sf::Style::Close);
	this->window.setFramerateLimit(60);

	this->background.setTexture(this->texmgr.getRef("background"));
}

Game::~Game()
{
	while (!this->states.empty())
		popState();

	delete player;
}