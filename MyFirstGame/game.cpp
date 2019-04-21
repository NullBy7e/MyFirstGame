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

namespace mfg
{
	namespace core
	{
		game::game()
		{
			sysmgr.reset(new system_manager);
			entmgr.reset(new entity_manager);
			texmgr.reset(new texture_manager);
			mapmgr.reset(new map_manager);

			window.reset(new mfg::core::window());
			window->create(sf::VideoMode(1280, 1024), "MyFirstGame", sf::Style::Titlebar | sf::Style::Close);
			window->setFramerateLimit(60);

			createPlayer();

			TmxParser parser;

			auto mapId = mapmgr->addMap(parser.parse("maps/level1/level1.tmx"));
			auto map = mapmgr->loadMap(mapId, texmgr.get(), entmgr.get());

			/* screen dimensions (window size) */
			screen_dimensions = sf::Vector2i(1280, 1024);

			viewport_dimensions = sf::Vector2f(screen_dimensions.x, screen_dimensions.y);
			viewport_tile_width = viewport_dimensions.x / map->tile_width;
			viewport_tile_height = viewport_dimensions.y / map->tile_height;

			/* the viewport view is used to enable side-scrolling, it acts as a camera for the player */
			viewport.setSize(viewport_dimensions);
			viewport.setCenter(viewport.getCenter().x + map->tile_width * 2.2, viewport.getCenter().y);
		}

		void game::updateViewport()
		{
			auto map = mapmgr->getCurrentMap();
			auto player_position = entmgr->getEntities().get<position>(entmgr->getPlayer());

			auto viewport_pos_x = player_position.x;
			auto viewport_pos_y = player_position.y;

			/* calculations to ensure that the viewport camera is never centered off the map's edges */
			auto move_camera_x = viewport_pos_x - (viewport_dimensions.x / 2) > 0 && viewport_pos_x + (viewport_dimensions.x / 2) < map->pixel_width;
			auto move_camera_y = viewport_pos_y - (viewport_dimensions.y / 2) > 0 && viewport_pos_y + (viewport_dimensions.y / 2) < map->pixel_height;

			if (move_camera_x)
			{
				viewport.setCenter(viewport_pos_x, viewport.getCenter().y);
			}

			if (move_camera_y)
			{
				viewport.setCenter(viewport.getCenter().x, viewport_pos_y);
			}

			/* set the viewport view */
			window->setView(viewport);
		}

		void game::drawTiles()
		{
			auto map = mapmgr->getCurrentMap();

			/* draw every tile that's inside the viewport */
			for (auto layer : map->tile_layers)
			{
				for (int col = ((viewport.getCenter().x / map->tile_width) - viewport_tile_width); col < map->width; ++col)
				{
					if (col < 0) //nothing to draw?
						continue;

					for (int row = ((viewport.getCenter().y / map->tile_height) - viewport_tile_height); row < map->height; ++row)
					{
						if (row < 0) //nothing to draw?
							continue;

						/* the tile number to draw */
						auto tile = layer.tiles[(row * map->width) + col];

						/* get the sprite that belongs to the tile number */
						auto& sprite = map->sprites[tile.id];

						/* set the sprite's position */
						sprite.setPosition(sf::Vector2f(col * map->tile_width, row * map->tile_height));

						window->draw(sprite);
					}
				}
			}
		}

		void game::drawEntities()
		{
			entmgr->getEntities().view<position, scale, sprite>().each([this](auto entity, auto &position, auto& scale, auto &sprite) {
				sprite.setPosition(position.x, position.y);
				sprite.setScale(scale.x, scale.y);

				this->window->draw(sprite);
			});
		}

		void game::createPlayer()
		{
			auto& entities = entmgr->getEntities();

			auto entity = entities.create();
			entities.assign<player>(entity);

			auto tex = texmgr->get("player", "textures/sprites/player/knight_f_run_anim_f1.png");
			entities.assign<sprite>(entity, sf::Sprite(tex));
			entities.assign<scale>(entity, scale{ 3.5, 3.5 });

			entmgr->setPlayer(entity);
		}

		void game::draw()
		{
			window->clear(sf::Color::Black);

			drawTiles();
			drawEntities();

			window->display();
		}

		void game::loop()
		{
			while (window->isOpen())
			{
				window->handleInput(mapmgr.get(), entmgr.get());

				updateViewport();
				draw();
			}
		}
	}
}