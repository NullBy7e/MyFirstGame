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
		Game::Game()
		{
			entmgr.reset(new EntityManager);
			sysmgr.reset(new SystemManager(entmgr.get()));
			texmgr.reset(new TextureManager);
			mapmgr.reset(new MapManager);

			window.reset(new mfg::core::Window());
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

		void Game::updateViewport()
		{
			auto map = mapmgr->getCurrentMap();

			auto& player = entmgr->getEntities().get<mfg::components::EntityComponent>(entmgr->getPlayer());
			auto player_position = sf::Vector2f(player.x, player.y);

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

		void Game::drawTiles()
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

		void Game::drawEntities()
		{
			entmgr->getEntities().each([this](auto entity)
			{
				auto& entity_component = entmgr->getEntities().get<mfg::components::EntityComponent>(entity);
				auto& sprite = entity_component.sprite;

				if (entmgr->getEntities().has<ActiveAnimationComponent>(entity))
				{
					ActiveAnimationComponent& anim = entmgr->getEntities().get<ActiveAnimationComponent>(entity);
					sprite = *anim.animation->sprite;
				}
				else
				{
					sprite.setScale({ entity_component.x_scale, entity_component.y_scale });
					sprite.setRotation(entity_component.rotation);
				}

				sprite.setPosition(entity_component.x, entity_component.y);
				this->window->draw(sprite);
			});
		}

		void Game::createPlayer()
		{
			auto& entities = entmgr->getEntities();

			auto entity = entities.create();

			auto tex = texmgr->get("player", "textures/sprites/player/animation/knight_m_idle_anim_f0.png");
			auto player_sprite = sf::Sprite(tex);

			entities.assign<mfg::components::EntityComponent>(entity, 0, 0, player_sprite.getLocalBounds().width, player_sprite.getLocalBounds().height, 1, 1, 0, false, player_sprite);

			/* the idle animation data */
			thor::FrameAnimation idle_frame_data;
			idle_frame_data.addFrame(2.f, sf::IntRect(0, 0, 64, 112));
			idle_frame_data.addFrame(2.f, sf::IntRect(0, 112, 64, 112));
			idle_frame_data.addFrame(2.f, sf::IntRect(0, 224, 64, 112));
			idle_frame_data.addFrame(2.f, sf::IntRect(0, 336, 64, 112));

			/* player animation texture and the resulting sprite */
			auto player_anim_texture = texmgr->get("idle", "textures/sprites/player/animation/knight_m_idle.png");
			auto player_anim_sprite = std::make_unique<sf::Sprite>(sf::Sprite(player_anim_texture));

			auto idle = IdleAnimationComponent{ player_anim_sprite.get(), idle_frame_data };
			sysmgr->getAnimationSystem()->addAnimation(entity, idle, sf::seconds(8.f));

			/* the run animation data */
			thor::FrameAnimation run_frame_data;
			run_frame_data.addFrame(0.25f, sf::IntRect(0, 0, 64, 112));
			run_frame_data.addFrame(0.25f, sf::IntRect(0, 112, 64, 112));
			run_frame_data.addFrame(0.25f, sf::IntRect(0, 224, 64, 112));
			run_frame_data.addFrame(0.25f, sf::IntRect(0, 336, 64, 112));

			/* player animation texture and the resulting sprite */
			auto player_anim_texture2 = texmgr->get("run", "textures/sprites/player/animation/knight_m_run.png");
			auto player_anim_sprite2 = std::make_unique<sf::Sprite>(sf::Sprite(player_anim_texture2));

			auto run = RunAnimationComponent{ player_anim_sprite2.get(), run_frame_data };
			sysmgr->getAnimationSystem()->addAnimation(entity, run, sf::seconds(1.f));

			entmgr->setPlayer(entity);
		}

		void Game::draw()
		{
			window->clear(sf::Color::Black);

			drawTiles();
			drawEntities();

			window->display();
		}

		void Game::loop()
		{
			sf::Clock clock;

			auto player = entmgr->getPlayer();

			auto animsys = sysmgr->getAnimationSystem();
			animsys->playAnimation<IdleAnimationComponent>(player, LOOP_ANIMATION::YES);

			while (window->isOpen())
			{
				/* draw everything */
				draw();

				/* elapsed time since last draw (frame/tick/w.e) */
				auto dt = clock.getElapsedTime();

				/* handle input */
				window->handleInput(sysmgr.get(), mapmgr.get(), entmgr.get(), dt);

				/* uodate animations */
				animsys->animate(clock.restart());

				/* update the viewport */
				updateViewport();
			}
		}
	}
}