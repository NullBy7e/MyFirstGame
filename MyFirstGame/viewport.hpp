#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>

#include "macros.hpp"

namespace mfg
{
	namespace core
	{
		class Viewport : public sf::View
		{
		public:
			Viewport();
			~Viewport();

			void update(sf::Vector2f target_position, sf::Vector2f map_dimensions);

			void setTileWidth(float width);
			void setTileHeight(float height);

			void setDimensions(sf::Vector2f dimensions);

			float getTileWidth();
			float getTileHeight();

			sf::Vector2f getDimensions();

		private:
			float tile_width;
			float tile_height;

			sf::Vector2f dimensions;
		};
	}
}