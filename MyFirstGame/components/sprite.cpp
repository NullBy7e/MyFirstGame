#include "sprite.hpp"

namespace mfg
{
	namespace components
	{
		SpriteComponent::SpriteComponent(bool mirrored, int width, int height, sf::Sprite sprite) : SpriteComponent(width, height, sprite)
		{
			if (mirrored)
				toggleMirror();
		}

		SpriteComponent::SpriteComponent(int width, int height, sf::Sprite sprite) : SpriteComponent(sprite)
		{
			auto bounds = sprite.getLocalBounds();

			auto factorX = width / bounds.width;
			auto factorY = height / bounds.height;

			if (mirrored)
				toggleMirror();
			else
				setScale(factorX, factorY);
		}

		SpriteComponent::SpriteComponent(bool mirrored, sf::Sprite sprite) : SpriteComponent(sprite)
		{
			if (mirrored)
				toggleMirror();
		}

		SpriteComponent::SpriteComponent(sf::Sprite sprite) : sf::Sprite(sprite)
		{
			auto bounds = sprite.getLocalBounds();
			setOrigin(bounds.width / 2, bounds.height);
		}

		SpriteComponent::SpriteComponent()
		{
		}

		SpriteComponent::~SpriteComponent()
		{
		}

		void SpriteComponent::toggleMirror()
		{
			mirrored = !mirrored;

			if (mirrored)
				setScale(-getScale().x, getScale().y);
		}

		void SpriteComponent::update(sf::Vector2f pos)
		{
			setPosition(pos);
		}
	}
}