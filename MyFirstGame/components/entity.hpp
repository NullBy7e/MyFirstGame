#pragma once

#include <SFML/Graphics.hpp>
#include "../utils/types.hpp"

using namespace mfg::utils;

namespace mfg {
	namespace components {
		struct entity_component
		{
			entity_component() {};

			entity_component(const int id, const std::string name, position position, scale scale, const sf::Sprite sprite) : id(id), name(name), position(position), scale(scale), sprite(sprite)
			{
				this->sprite.setPosition(position.x, position.y);
				this->sprite.setScale(scale.x, scale.y);
			};

			int id;
			std::string name;

			position position;
			scale scale;
			sf::Sprite sprite;
		};
	}
}