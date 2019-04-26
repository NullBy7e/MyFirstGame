#pragma once

#include <iostream>

#include "macros.hpp"

#include "map.hpp"
#include "viewport.hpp"

namespace mfg
{
	namespace core
	{
		class MapRenderer
		{
		public:
			MapRenderer();
			~MapRenderer();

			std::vector<sf::Sprite> getSprites(Viewport* viewport, Map* map);

		private:
			std::vector<sf::Sprite> drawTiles(Viewport* viewport, Map* map);
			std::vector<sf::Sprite> drawEntities(Map* map);
		};
	}
}