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
		void Window::handleInput(SystemManager* sysmgr, MapManager* mapmgr, EntityManager* entmgr, sf::Time dt)
		{
			sf::Event event{};

			auto& map      = mapmgr->getCurrentMap();
			auto& entities = entmgr->getEntities();

			const auto player_entity = entmgr->getPlayer();
			auto&      player        = entities.get<EntityComponent>(player_entity);

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
								const auto player_position = sf::Vector2f(player.x, player.y);

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
								default:
									break;
								}

								if (move_speed == 0)
									return;

								const auto new_pos = move_speed * dt.asSeconds();

								const auto delta    = (player_position.x + new_pos) - player_position.x;
								const auto can_move = player_position.x + delta > 0 && player_position.x + delta < ((map
									.width * map.tile_width) - map.tile_width);

								if (can_move)
								{
									player.x += new_pos;

									if (entmgr->getEntities().has<ActiveAnimationComponent>(player_entity))
									{
										auto& anim = entmgr->getEntities().get<ActiveAnimationComponent>(player_entity);
										if (anim.name != "run_animation")
										{
											animsys->stopAnimation(player_entity);
										}
									}

									/* play the run_animation */
									animsys->playAnimation<RunAnimationComponent>(player_entity);

									clock_.restart();
								}
							}
						default:
							break;
						}
						break;
					}
				case sf::Event::Closed:
					{
						close();
						break;
					}
				default:
					break;
				}
			}

			elapsed_time_ = clock_.getElapsedTime();
			if (elapsed_time_.asSeconds() >= 2)
			{
				animsys->playAnimation<IdleAnimationComponent>(player_entity, loop_animation::yes);
				elapsed_time_ = sf::Time::Zero;
			}

			/* we need to update any active animations with the proper scaling values */
			/* to ensure that it's facing the correct angle */
			if (player.facing_left || player.facing_right)
			{
				auto& anim = entmgr->getEntities().get<ActiveAnimationComponent>(player_entity);

				if (player.facing_left)
					anim.animation->sprite->setScale(-1, 1);

				if (player.facing_right)
					anim.animation->sprite->setScale(1, 1);
			}
		}

		Window& Window::getRef()
		{
			return *this;
		}
	}
}
