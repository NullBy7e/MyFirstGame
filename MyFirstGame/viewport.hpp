#pragma once

#include <SFML/Graphics.hpp>

namespace mfg
{
	namespace core
	{
		class Viewport : public sf::View
		{
		public:
			Viewport() = default;

			void update(sf::Vector2f target_position, sf::Vector2f map_dimensions);

			void setTileWidth(float  width);
			void setTileHeight(float height);

			void setDimensions(sf::Vector2f dimensions);

			float getTileWidth() const;
			float getTileHeight() const;

			sf::Vector2f getDimensions() const;

			Viewport& getRef();

		private:
			float tile_width_{};
			float tile_height_{};

			sf::Vector2f dimensions_;
		};
	}
}
