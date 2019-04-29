#include "sprite.hpp"

namespace mfg
{
	namespace components
	{
		SpriteComponent::
		SpriteComponent(const bool mirrored, const float width, const float height, const Sprite& sprite) :
			SpriteComponent(
				width, height, sprite)
		{
			if (mirrored)
				toggleMirror();
		}

		SpriteComponent::
		SpriteComponent(const float width, const float height, const Sprite& sprite) : SpriteComponent(sprite)
		{
			const auto bounds = sprite.getLocalBounds();

			const auto factor_x = width / bounds.width;
			const auto factor_y = height / bounds.height;

			if (mirrored_)
				toggleMirror();
			else
				setScale(factor_x, factor_y);
		}

		SpriteComponent::SpriteComponent(const bool mirrored, const Sprite& sprite) : SpriteComponent(sprite)
		{
			if (mirrored)
				toggleMirror();
		}

		SpriteComponent::SpriteComponent(const Sprite& sprite) : Sprite(sprite)
		{
			const auto bounds = sprite.getLocalBounds();
			setOrigin(bounds.width / 2, bounds.height);
		}

		void SpriteComponent::toggleMirror()
		{
			mirrored_ = !mirrored_;

			if (mirrored_)
				setScale(-getScale().x, getScale().y);
		}

		void SpriteComponent::update(const sf::Vector2f position)
		{
			setPosition(position);
		}
	}
}
