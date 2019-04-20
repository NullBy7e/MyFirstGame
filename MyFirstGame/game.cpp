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

using namespace mfg::components;
using namespace mfg::caching;
using namespace mfg::managers;

namespace mfg
{
	namespace core
	{
		game::game()
		{
			window.reset(new mfg::core::window());

			window->create(sf::VideoMode(1280, 1024), "MyFirstGame", sf::Style::Titlebar | sf::Style::Close);
			window->setFramerateLimit(60);

			/* load the map */
			TmxParser parser;
			map = std::make_unique<TmxMap>(parser.parse("maps/level1/level1.tmx"));

			/* iterate through each tileset */
			for (int i = 0; i < map->tilesets.size(); i++)
			{
				auto tileset = map->tilesets[i];
				auto tex = textures.load<texture_loader>(entt::hashed_string::to_value(tileset.name.c_str()), tileset.image.image_source);

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
						sf::Sprite sprite(tex.get(), sf::IntRect(xpos, ypos, tileset.tile_width, tileset.tile_height));

						sprites[tn] = sprite;
					}
				}
			}

			/* object layers */
			for (auto& layer : map->object_layers)
			{
				for (auto& object : layer.objects)
				{
					auto new_sprite = sf::Sprite(sprites[object.gid]);

					/* load player texture into new_sprite here to prevent scale/sizing conflicts */
					if (object.name == "player_spawn" && object.type == "player")
					{
						auto tex = textures.load<texture_loader>("player"_hs, "../../textures/sprites/player/knight_f_run_anim_f1.png");
						new_sprite.setTexture(tex.get(), true);
					}

					sf::Vector2f targetSize(object.width, object.height);

					auto bounds = new_sprite.getLocalBounds();

					float x_scale = targetSize.x / bounds.width;
					float y_scale = targetSize.y / bounds.height;

					auto x_pos = object.x;
					auto y_pos = object.y - object.height;

					/* check flips */
					if (object.flipped_horizontally)
					{
						x_pos = object.x + object.width;
					}

					auto entities = MFG::getEntityManager()->getEntities();

					auto entity = entities->create();
					entities->assign<position>(entity, x_pos, y_pos);
					entities->assign<scale>(entity, x_scale, y_scale);
					entities->assign<sprite>(entity, new_sprite);

					if (object.name == "player_spawn" && object.type == "player")
					{
						entities->assign<player>(entity);
						player_entity = entity;

						player_spawned = true;
					}

					if (object.type == "enemy")
					{
						entities->assign<enemy>(entity);
					}
				}
			}

			/* screen dimensions (window size) */
			screen_dimensions = sf::Vector2i(1280, 1024);

			/* local map properties */
			tile_size = sf::Vector2f(map->tile_width, map->tile_height);

			map_tile_width = map->width;
			map_tile_height = map->height;
			map_dimensions = sf::Vector2f(map_tile_width * tile_size.x, map_tile_height * tile_size.y);

			viewport_dimensions = sf::Vector2f(screen_dimensions.x, screen_dimensions.y);
			viewport_tile_width = viewport_dimensions.x / tile_size.x;
			viewport_tile_height = viewport_dimensions.y / tile_size.y;

			/* the viewport view is used to enable side-scrolling, it acts as a camera for the player */
			viewport.setSize(viewport_dimensions);
		}

		void game::updateViewport()
		{
			auto player_position = MFG::getEntityManager()->getEntities()->get<position>(player_entity);

			auto viewport_pos_x = player_position.x;
			auto viewport_pos_y = player_position.y;

			/* calculations to ensure that the viewport camera is never centered off the map's edges */
			auto move_camera_x = viewport_pos_x - (viewport_dimensions.x / 2) > 0 && viewport_pos_x + (viewport_dimensions.x / 2) < map_dimensions.x;
			auto move_camera_y = viewport_pos_y - (viewport_dimensions.y / 2) > 0 && viewport_pos_y + (viewport_dimensions.y / 2) < map_dimensions.y;

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
			/* draw every tile that's inside the viewport */
			for (auto layer : map->tile_layers)
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
						auto tile = layer.tiles[(row * map->width) + col];

						/* get the sprite that belongs to the tile number */
						auto& sprite = sprites[tile.id];

						/* set the sprite's position */
						sprite.setPosition(sf::Vector2f(col * tile_size.x, row * tile_size.y));

						window->draw(sprite);
					}
				}
			}
		}

		void game::drawEntities()
		{
			MFG::getEntityManager()->getEntities()->view<position, scale, sprite>().each([this](auto entity, auto &position, auto& scale, auto &sprite) {
				sprite.setPosition(position.x, position.y);
				sprite.setScale(scale.x, scale.y);

				this->window->draw(sprite);
			});
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
				window->handleInput(player_entity);

				updateViewport();
				draw();
			}
		}
	}
}