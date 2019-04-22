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

#include "window.hpp"

namespace mfg
{
	namespace core
	{
		void window::handleInput(system_manager* sysmgr, map_manager* mapmgr, entity_manager* entmgr, sf::Time dt)
		{
			sf::Event event;

			auto map = mapmgr->getCurrentMap();
			auto& entities = entmgr->getEntities();

			auto player_entity = entmgr->getPlayer();
			auto& player = entities.get<mfg::components::entity>(player_entity);

			auto animsys = sysmgr->getAnimationSystem();

			while (this->pollEvent(event))
			{
				switch (event.type)
				{
				case sf::Event::KeyPressed:
				{
					switch (event.key.code)
					{
					case sf::Keyboard::W:
					case sf::Keyboard::A:
					case sf::Keyboard::S:
					case sf::Keyboard::D:
					{
						auto player_position = sf::Vector2f(player.x, player.y);

						auto move_speed = 0.f;

						switch (event.key.code)
						{
						case sf::Keyboard::A:
						{
							if (!player.facing_left)
							{
								player.setFacingLeft();
							}

							move_speed = -player.move_speed;
							break;
						}
						case sf::Keyboard::D:
						{
							if (!player.facing_right)
							{
								player.setFacingRight();
							}

							move_speed = player.move_speed;
							break;
						}
						}

						if (move_speed == 0)
							return;

						auto new_pos = move_speed * dt.asSeconds();

						auto delta = (player_position.x + new_pos) - player_position.x;
						auto can_move = player_position.x + delta > 0 && player_position.x + delta < ((map->width * map->tile_width) - map->tile_width);

						if (can_move)
						{
							player.x += new_pos;

							if (entmgr->getEntities().has<active_animation>(player_entity))
							{
								auto& anim = entmgr->getEntities().get<active_animation>(player_entity);
								if (anim.name != "run_animation")
								{
									animsys->stopAnimation(player_entity);
								}
							}

							/* play the run_animation */
							animsys->playAnimation<run_animation>(player_entity);

							clock.restart();
						}
					}
					default: break;
					}
					break;
				}
				case sf::Event::Closed:
				{
					close();
					break;
				}
				}
			}

			elapsed_time = clock.getElapsedTime();
			if (elapsed_time.asSeconds() >= 2)
			{
				animsys->playAnimation<idle_animation>(player_entity, LOOP_ANIMATION::YES);
				elapsed_time = elapsed_time.Zero;
			}

			/* we need to update any active animations with the proper scaling values */
			/* to ensure that it's facing the correct angle */
			if (player.facing_left || player.facing_right)
			{
				auto& anim = entmgr->getEntities().get<active_animation>(player_entity);

				if (player.facing_left)
					anim.animation->sprite->setScale(-1, 1);

				if (player.facing_right)
					anim.animation->sprite->setScale(1, 1);
			}
		}
	}
}