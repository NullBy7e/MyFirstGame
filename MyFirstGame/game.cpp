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

#include "game.hpp"
#include "entt/entt.hpp"

using namespace core;

void game::load()
{
	window.create(sf::VideoMode(1280, 1024), "MyFirstGame", sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(60);
}

void game::loop()
{
	/* screen dimensions (window size) */
	sf::Vector2i screen_dimensions(1280, 1024);

	/* texture manager */
	texture_manager texmgr;
	texmgr.loadTexture("player", "textures/sprites/player/knight_f_run_anim_f1.png");

	/* load the map */
	TmxParser parser;
	auto map = parser.parse("maps/level1/level1.tmx");

	/* array that maps tile number to sprite (contains all sprites from the tileset and the number that
	 * Tiled would normally assign to it */
	std::map<int, sf::Sprite> sprites;

	/* iterate through each tileset */
	for (int i = 0; i < map.tilesets.size(); i++)
	{
		auto tileset = map.tilesets[i];
		texmgr.loadTexture(tileset.name, tileset.image.image_source);

		auto& tex = texmgr.getRef(tileset.name);

		/* iterate through each row */
		for (int row = 0; row < (tileset.tile_count / tileset.columns); ++row)
		{
			/* indicates at which Y pos this row starts */
			auto row_start_y_pos = row * tileset.tile_height;

			/* iterate through each column */
			for (int col = 0; col < tileset.columns; col++)
			{
				/* the tile number used by Tiled */
				auto tn = (tileset.first_gid + col) + (row * tileset.columns);

				/* X & Y pos calculation */
				auto xpos = col * tileset.tile_width;
				auto ypos = row_start_y_pos;

				/* Make a new sprite */
				sf::Sprite sprite(tex, sf::IntRect(xpos, ypos, tileset.tile_width, tileset.tile_height));
				sprites[tn] = sprite;
			}
		}
	}

	/* local map properties */
	auto tile_size = sf::Vector2f(map.tile_width, map.tile_height);

	auto map_tile_width = map.width;
	auto map_tile_height = map.height;
	auto map_dimensions = sf::Vector2f(map_tile_width * tile_size.x, map_tile_height * tile_size.y);

	auto viewport_dimensions = sf::Vector2f(screen_dimensions.x, screen_dimensions.y);
	auto viewport_tile_width = viewport_dimensions.x / tile_size.x;
	auto viewport_tile_height = viewport_dimensions.y / tile_size.y;

	auto player_start_tile_x = 0;
	auto player_start_tile_y = 13;

	auto player_start_tile_offset_x = viewport_tile_width / 2;
	auto player_start_tile_offset_y = viewport_tile_height / 3.2;

	/* the viewport view is used to enable side-scrolling, it acts as a camera for the player */
	sf::View viewport;
	viewport.setCenter(sf::Vector2f(player_start_tile_x * tile_size.x, player_start_tile_y * tile_size.y));
	viewport.setSize(viewport_dimensions);
	viewport.move(sf::Vector2f(player_start_tile_offset_x * tile_size.x, -(player_start_tile_offset_y * tile_size.y)));

	while (window.isOpen())
	{
		/* handle window events */
		window.handleInput(viewport);

		/* clear */
		window.clear(sf::Color::Black);

		/* set the viewport view */
		window.setView(viewport);

		/* draw every tile that's inside the viewport */
		for (auto layer : map.tile_layers)
		{
			for (int col = ((viewport.getCenter().x / tile_size.x) - viewport_tile_width); col < map_tile_width; ++col)
			{
				if (col < 0) //nothing to draw?
					continue;

				for (int row = ((viewport.getCenter().y / tile_size.y) - viewport_tile_height); row < map_tile_height; ++row)
				{
					if (row < 0) //nothing to draw?
						continue;

					/* the tile number to draw */
					auto tile = layer.tiles[(row * map.width) + col];

					/* get the sprite that belongs to the tile number */
					auto sprite = sprites[tile.id];

					/* set the sprite's position */
					sprite.setPosition(sf::Vector2f(col * tile_size.x, row * tile_size.y));

					window.draw(sprite);
				}
			}
		}

		window.display();
	}
}

void game::drawXYChart()
{
	/* screen dimensions (window size) */
	sf::Vector2i screen_dimensions(1280, 1024);

	/* font */
	sf::Font font;
	if (!font.loadFromFile("fonts/arial.ttf"))
	{
		std::cout << "Error loading font\n";
	}

	auto tile_size = sf::Vector2f(64, 64);

	auto map_tile_width = 40;
	auto map_tile_height = 32;

	auto viewport_tile_width = screen_dimensions.x / tile_size.x;
	auto viewport_tile_height = screen_dimensions.y / tile_size.y;

	auto viewport_dimensions = sf::Vector2f(screen_dimensions.x, screen_dimensions.y);

	/* this is what contains all the columns and rows except those that are drawn in the viewport */
	sf::View main(window.getDefaultView());

	sf::View viewport;
	viewport.setCenter(viewport_dimensions);
	viewport.setSize(viewport_dimensions);
	viewport.move(screen_dimensions.x / 2, screen_dimensions.y / 2);

	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(18);
	text.setFillColor(sf::Color::Black);

	sf::Text text2;
	text2.setFont(font);
	text2.setCharacterSize(18);
	text2.setFillColor(sf::Color::Black);

	sf::RectangleShape tile;
	tile.setSize(tile_size);
	tile.setOutlineThickness(1.f);
	tile.setOutlineColor(sf::Color::Black);

	while (window.isOpen())
	{
		/* handle window events */
		window.handleInput(viewport);

		/* clear */
		window.clear(sf::Color::Black);

		/* set the main view */
		window.setView(main);

		/* draw the columns and rows until the start of the main viewport */
		for (int col = 0; col < viewport_tile_width; ++col)
		{
			for (int row = 0; row < viewport_tile_height; ++row)
			{
				sf::RectangleShape square(tile);
				square.setPosition(sf::Vector2f(col * tile_size.x, row * tile_size.y));

				text.setString(sf::String("X " + std::to_string((int)(row * tile_size.y))));
				text.setPosition(sf::Vector2f(col * tile_size.x, row * tile_size.y));

				text2.setString(sf::String("Y " + std::to_string((int)(col * tile_size.x))));
				text2.setPosition(sf::Vector2f(col * tile_size.x, (row * tile_size.y) + 25));

				window.draw(square);

				window.draw(text);
				window.draw(text2);
			}
		}

		/* set the viewport view */
		window.setView(viewport);

		/* draw the columns and rows for the viewport */
		for (int col = viewport_tile_width; col < map_tile_width; ++col)
		{
			for (int row = viewport_tile_height; row < map_tile_height; ++row)
			{
				sf::RectangleShape square(tile);
				square.setPosition(sf::Vector2f(col * tile_size.x, row * tile_size.y));

				text.setString(sf::String("X " + std::to_string((int)(row * tile_size.y))));
				text.setPosition(sf::Vector2f(col * tile_size.x, row * tile_size.y));

				text2.setString(sf::String("Y " + std::to_string((int)(col * tile_size.x))));
				text2.setPosition(sf::Vector2f(col * tile_size.x, (row * tile_size.y) + 25));

				window.draw(square);

				window.draw(text);
				window.draw(text2);
			}
		}

		viewport.move(-2.f, .0f);

		/* display all drawn stuff */
		window.display();
	}
}