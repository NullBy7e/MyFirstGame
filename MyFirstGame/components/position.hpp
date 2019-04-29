#pragma once

#include <SFML/Graphics.hpp>

namespace mfg
{
	namespace components
	{
		class PositionComponent
		{
		public:
			PositionComponent() = default;
			PositionComponent(float x, float y);

			void setPosition(float x, float y);

			sf::Vector2f getPosition() const;
			sf::Vector2f getPosition(float height_offset) const;

		private:

			float x_{};
			float y_{};
		};
	}
}
