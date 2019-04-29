#pragma once

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
			explicit MapRenderer(Window& window);

			void render(Viewport& viewport, Map& map) const;

		private:
			void drawTiles(Viewport& viewport, Map& map) const;
			void drawEntities(Map&   map) const;

			Window& window_;
		};
	}
}
