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
		void window::handleInput(map_manager* mapmgr, entity_manager* entmgr)
		{
			sf::Event event;

			auto map = mapmgr->getCurrentMap();

			auto& entities = entmgr->getEntities();
			auto player = entmgr->getPlayer();

			auto& player_position = entities.get<position>(player);

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
						auto move = 0;

						switch (event.key.code)
						{
						case sf::Keyboard::W: break;
						case sf::Keyboard::A: move = -25; break;
						case sf::Keyboard::S: break;
						case sf::Keyboard::D: move = 25;  break;
						}

						if (move == 0)
							return;

						auto delta = (player_position.x + move) - player_position.x;
						auto can_move = player_position.x + delta > 0 && player_position.x + delta < ((map->width * map->tile_width) - map->tile_width);

						if (can_move)
						{
							player_position.x += move;
						}
					}
					default: break;
					}
					break;
				}
				case sf::Event::Closed:
				{
					this->close();
					break;
				}
				}
			}
		}
	}
}