#pragma once

#include <SFML/Graphics.hpp>
#include "../components/components.hpp"

using namespace mfg::components;

namespace mfg
{
	namespace events
	{
		struct player_move
		{
			player_move(int key, position& position) : key(key), position(position) {};

			int key;
			position& position;
		};
	}
}