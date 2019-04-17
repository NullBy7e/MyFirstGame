#include "game.h"

Game::Game()
{
}

Game::~Game()
{
}

void Game::Load()
{
	this->window_.create(sf::VideoMode(1280, 1024), "MyFirstGame", sf::Style::Titlebar | sf::Style::Close);
	this->window_.setFramerateLimit(60);
	this->window_.setMouseCursorVisible(false);
}

void Game::Loop()
{
	TmxParser parser;
	auto map = parser.parse("maps/level1/level1.tmx");

	while (this->window_.isOpen())
	{
		this->window_.HandleInput();

		this->window_.clear(sf::Color::Black);
		this->window_.display();
	}
}