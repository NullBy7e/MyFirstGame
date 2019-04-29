#pragma once

#include <SFML/Graphics.hpp>

namespace mfg
{
	namespace components
	{
		class SpriteComponent final : public sf::Sprite
		{
		public:
			SpriteComponent(bool  mirrored, float width, float          height, const Sprite& sprite);
			SpriteComponent(float width, float    height, const Sprite& sprite);

			         SpriteComponent(bool          mirrored, const Sprite& sprite);
			explicit SpriteComponent(const Sprite& sprite);

			SpriteComponent() = default;

			void toggleMirror();
			void update(sf::Vector2f position);

		private:
			bool mirrored_ = false;
		};
	}
}
