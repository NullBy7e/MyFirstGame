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
		void window::handleInput(entt::entity player)
		{
			sf::Event event;

			auto input = MFG::getSystemManager()->getInputSystem();
			auto entities = MFG::getEntityManager()->getEntities();

			auto& player_position = entities->get<position>(player);

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
						player_move move
						{
							event.key.code,
							player_position
						};

						input->dispatcher.enqueue<player_move>(move);
						input->dispatcher.update<player_move>();
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