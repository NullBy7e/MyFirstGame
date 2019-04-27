#pragma once

#include <iostream>

#include "macros.hpp"
#include "window.hpp"

#include "map.hpp"
#include "viewport.hpp"

namespace mfg
{
	namespace core
	{
		class MapRenderer
		{
		public:
			MapRenderer(Window& window);
			~MapRenderer();

			void render(Viewport& viewport, Map& map);

		private:
			void drawTiles(Viewport& viewport, Map& map);
			void drawEntities(Map& map);

			Window& window;
		};
	}
}