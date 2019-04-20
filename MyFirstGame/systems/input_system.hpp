#pragma once

#include "entt/entt.hpp"
#include "../events/player_move.hpp"
#include "../managers/map_manager.hpp"

using namespace mfg::events;
using namespace mfg::managers;

namespace mfg
{
	namespace systems
	{
		class input_system
		{
		public:
			input_system()
			{
				dispatcher.sink<player_move>().connect<&input_system::receive>(this);
			};

			entt::dispatcher dispatcher{};

			void receive(const player_move& e)
			{
				auto map = map_manager::getInstance()->getCurrentMap();

				auto move = 0;

				switch (e.key)
				{
				case sf::Keyboard::W: break;
				case sf::Keyboard::A: move = -25; break;
				case sf::Keyboard::S: break;
				case sf::Keyboard::D: move = 25;  break;
				}

				if (move == 0)
					return;

				auto delta = (e.position.x + move) - e.position.x;
				auto can_move = e.position.x + delta > 0 && e.position.x + delta < ((map->width * map->tile_width) - map->tile_width);

				if (can_move)
				{
					e.position.x += move;
				}
			}
		};
	}
}