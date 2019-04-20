#pragma once

#include <SFML/Graphics.hpp>

namespace mfg {
	namespace components {
		struct sprite : public sf::Sprite
		{
			sprite(sf::Sprite sprite) : sf::Sprite(sprite)
			{
			}
		};
	}
}