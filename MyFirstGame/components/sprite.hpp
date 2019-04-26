#pragma once

#include <SFML/Graphics.hpp>

namespace mfg {
	namespace components {
		class SpriteComponent : public sf::Sprite
		{
		public:
			SpriteComponent(bool mirrored, int width, int height, sf::Sprite sprite);
			SpriteComponent(int width, int height, sf::Sprite sprite);

			SpriteComponent(bool mirrored, sf::Sprite sprite);
			SpriteComponent(sf::Sprite sprite);

			SpriteComponent();
			~SpriteComponent();

			void toggleMirror();
			void update(sf::Vector2f position);

		private:
			bool mirrored = false;
		};
	}
}