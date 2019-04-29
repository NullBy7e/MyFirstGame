#include "viewport.hpp"

namespace mfg
{
	namespace core
	{
		void Viewport::update(const sf::Vector2f target_position, const sf::Vector2f map_dimensions)
		{
			const auto move_camera_x = target_position.x - (getDimensions().x / 2) > 0 && target_position.x + (
				getDimensions().x / 2) < map_dimensions.x;
			const auto move_camera_y = target_position.y - (getDimensions().y / 2) > 0 && target_position.y + (
				getDimensions().y / 2) < map_dimensions.y;

			if (move_camera_x)
			{
				setCenter(target_position.x, getCenter().y);
			}

			if (move_camera_y)
			{
				setCenter(getCenter().x, target_position.y);
			}
		}

		void Viewport::setTileWidth(const float width)
		{
			tile_width_ = width;
		}

		void Viewport::setTileHeight(const float height)
		{
			tile_height_ = height;
		}

		void Viewport::setDimensions(const sf::Vector2f dimensions)
		{
			this->dimensions_ = dimensions;
			setSize(dimensions);
		}

		float Viewport::getTileWidth() const
		{
			return tile_width_;
		}

		float Viewport::getTileHeight() const
		{
			return tile_height_;
		}

		sf::Vector2f Viewport::getDimensions() const
		{
			return dimensions_;
		}

		Viewport& Viewport::getRef()
		{
			return *this;
		}
	}
}
