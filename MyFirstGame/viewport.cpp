#include "viewport.hpp"

namespace mfg
{
	namespace core
	{
		Viewport::Viewport()
		{
			DEBUG_MSG("CTOR " << "	 [" << std::addressof(*this) << "]	Viewport");
		}

		Viewport::~Viewport()
		{
			DEBUG_MSG("DTOR " << "	 [" << std::addressof(*this) << "]	MapRenderer");
		}

		void Viewport::update(sf::Vector2f target_position, sf::Vector2f map_dimensions)
		{
			auto move_camera_x = target_position.x - (getDimensions().x / 2) > 0 && target_position.x + (getDimensions().x / 2) < map_dimensions.x;
			auto move_camera_y = target_position.y - (getDimensions().y / 2) > 0 && target_position.y + (getDimensions().y / 2) < map_dimensions.y;

			if (move_camera_x)
			{
				setCenter(target_position.x, getCenter().y);
			}

			if (move_camera_y)
			{
				setCenter(getCenter().x, target_position.y);
			}
		}

		void Viewport::setTileWidth(float width)
		{
			tile_width = width;
		}

		void Viewport::setTileHeight(float height)
		{
			tile_height = height;
		}

		void Viewport::setDimensions(sf::Vector2f dimensions)
		{
			this->dimensions = dimensions;
			setSize(dimensions);
		}

		float Viewport::getTileWidth() const
		{
			return tile_width;
		}

		float Viewport::getTileHeight() const
		{
			return tile_height;
		}

		sf::Vector2f Viewport::getDimensions()
		{
			return dimensions;
		}

		Viewport& Viewport::getRef()
		{
			return *this;
		}
	}
}