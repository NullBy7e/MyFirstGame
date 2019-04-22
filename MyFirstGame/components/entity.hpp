#pragma once

#include <SFML/Graphics.hpp>

#include "../macros.hpp"

namespace mfg {
	namespace components {
		class entity
		{
		public:
			entity(
				float x,
				float y,
				float width,
				float height,
				float x_scale,
				float y_scale,
				float rotation,
				bool flipped_horizontally,
				sf::Sprite sprite);

			void setFacingLeft();
			void setFacingRight();

			float x;
			float y;

			float width;
			float height;

			float x_scale;
			float y_scale;

			float rotation;

			bool facing_left = false;
			bool facing_right = false;

			bool flipped_horizontally = false;

			float move_speed = 300.f;

			sf::Sprite sprite;
		};
	}
}