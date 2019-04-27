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
			DEBUG_MSG("CTOR " << "	 [" << std::addressof(*this) << "]	Game");

			window.create(sf::VideoMode(1280, 1024), "MyFirstGame", sf::Style::Titlebar | sf::Style::Close);
			window.setFramerateLimit(60);

			TmxParser parser;
			auto mapId = mapmgr.addMap(parser.parse("maps/level1/level1.tmx"));
			auto& map = mapmgr.loadMap(mapId, texmgr.getRef());

			map.setPlayerData(createPlayerData());

			/* screen dimensions (window size) */
			screen_dimensions = sf::Vector2i(1280, 1024);

			viewport.setDimensions(sf::Vector2f(screen_dimensions.x, screen_dimensions.y));
			viewport.setTileWidth(viewport.getDimensions().x / map.tile_width);
			viewport.setTileHeight(viewport.getDimensions().y / map.tile_height);

			/* the viewport view is used to enable side-scrolling, it acts as a camera for the player */
			viewport.setCenter(viewport.getCenter().x + map.tile_width * 2.2, viewport.getCenter().y);
		}

		Game::~Game()
		{
			DEBUG_MSG("DTOR " << "	 [" << std::addressof(*this) << "]	 Game");
		}

		void Game::updateViewport()
		{
			auto& map = mapmgr.getCurrentMap();
			viewport.update(map.getPlayerPosition(), map.getDimensions());

			window.setView(viewport.getRef());
		}

		//void Game::drawEntities()
		//{
		//	entmgr->getEntities().each([this](auto entity)
		//	{
		//		auto& entity_component = entmgr->getEntities().get<mfg::components::EntityComponent>(entity);
		//		auto& sprite = entity_component.sprite;

		//		if (entmgr->getEntities().has<ActiveAnimationComponent>(entity))
		//		{
		//			ActiveAnimationComponent& anim = entmgr->getEntities().get<ActiveAnimationComponent>(entity);
		//			sprite = *anim.animation->sprite;
		//		}
		//		else
		//		{
		//			sprite.setScale({ entity_component.x_scale, entity_component.y_scale });
		//			sprite.setRotation(entity_component.rotation);
		//		}

		//		sprite.setPosition(entity_component.x, entity_component.y);
		//		this->window.draw(sprite);
		//	});
		//}

		PlayerData Game::createPlayerData()
		{
			auto tex = texmgr.get("player", "textures/sprites/player/animation/knight_m_idle_anim_f0.png");

			PlayerData player_data =
			{
				ActorComponent("player"),
				HealthComponent(400),
				AnimationComponent(),
				SpriteComponent(sf::Sprite(tex)),
				PositionComponent()
			};

			return player_data;

			//auto& entities = entmgr->getEntities();

			//auto entity = entities.create();

			//auto tex = texmgr->get("player", "textures/sprites/player/animation/knight_m_idle_anim_f0.png");
			//auto player_sprite = sf::Sprite(tex);

			//entities.assign<mfg::components::EntityComponent>(entity, 0, 0, player_sprite.getLocalBounds().width, player_sprite.getLocalBounds().height, 1, 1, 0, false, player_sprite);

			///* the idle animation data */
			//thor::FrameAnimation idle_frame_data;
			//idle_frame_data.addFrame(2.f, sf::IntRect(0, 0, 64, 112));
			//idle_frame_data.addFrame(2.f, sf::IntRect(0, 112, 64, 112));
			//idle_frame_data.addFrame(2.f, sf::IntRect(0, 224, 64, 112));
			//idle_frame_data.addFrame(2.f, sf::IntRect(0, 336, 64, 112));

			///* player animation texture and the resulting sprite */
			//auto player_anim_texture = texmgr->get("idle", "textures/sprites/player/animation/knight_m_idle.png");
			//auto player_anim_sprite = std::make_unique<sf::Sprite>(sf::Sprite(player_anim_texture));

			//auto idle = IdleAnimationComponent{ player_anim_sprite.get(), idle_frame_data };
			//sysmgr->getAnimationSystem()->addAnimation(entity, idle, sf::seconds(8.f));

			///* the run animation data */
			//thor::FrameAnimation run_frame_data;
			//run_frame_data.addFrame(0.25f, sf::IntRect(0, 0, 64, 112));
			//run_frame_data.addFrame(0.25f, sf::IntRect(0, 112, 64, 112));
			//run_frame_data.addFrame(0.25f, sf::IntRect(0, 224, 64, 112));
			//run_frame_data.addFrame(0.25f, sf::IntRect(0, 336, 64, 112));

			///* player animation texture and the resulting sprite */
			//auto player_anim_texture2 = texmgr->get("run", "textures/sprites/player/animation/knight_m_run.png");
			//auto player_anim_sprite2 = std::make_unique<sf::Sprite>(sf::Sprite(player_anim_texture2));

			//auto run = RunAnimationComponent{ player_anim_sprite2.get(), run_frame_data };
			//sysmgr->getAnimationSystem()->addAnimation(entity, run, sf::seconds(1.f));

			//entmgr->setPlayer(entity);
		}

		void Game::loop()
		{
			sf::Event event;
			MapRenderer renderer(window);

#ifdef DEBUG
			DebugOverlay debug_overlay(mapmgr.getCurrentMap().getEntityManager(), window);
#endif

			while (window.isOpen())
			{
				clear();

				window.pollEvent(event);
				updateViewport();

				renderer.render(viewport, mapmgr.getCurrentMap());

#ifdef DEBUG
				window.draw(debug_overlay);
#endif

				display();
			}
		}

		void Game::clear()
		{
			window.clear(sf::Color::Black);
		}

		void Game::display()
		{
			window.display();
		}

		sf::Time Game::restartClock()
		{
			return clock.restart();
		}

		float Game::getElapsedFrameTime()
		{
			return clock.getElapsedTime().asSeconds();
		}
	}
}