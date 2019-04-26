#pragma once

#include <SFML/Graphics.hpp>

namespace mfg {
	namespace components {
		class PositionComponent
		{
		public:
			PositionComponent();
			PositionComponent(float x, float y);
			~PositionComponent();

			void setPosition(float x, float y);

			sf::Vector2f getPosition();
			sf::Vector2f getPosition(float height_offset);

		private:

			float x;
			float y;
		};
	}
}