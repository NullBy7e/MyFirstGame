#include "entity.hpp"

namespace mfg {
	namespace components {
		entity::entity(
			float x,
			float y,
			float width,
			float height,
			float x_scale,
			float y_scale,
			float rotation,
			bool flipped_horizontally,
			sf::Sprite sprite)
			:
			x(x),
			y(y),
			width(width),
			height(height),
			x_scale(x_scale),
			y_scale(y_scale),
			rotation(rotation),
			flipped_horizontally(flipped_horizontally),
			sprite(sprite)
		{
		}

		void entity::setFacingLeft()
		{
			sprite.setScale({ -1, 1 });

			facing_right = false;
			facing_left = true;
		}

		void entity::setFacingRight()
		{
			sprite.setScale({ 1, 1 });

			facing_left = false;
			facing_right = true;
		}
	}
}