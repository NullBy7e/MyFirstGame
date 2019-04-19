#pragma once

#include <SFML/Graphics.hpp>
#include "entity.hpp"

using namespace mfg::utils;

namespace mfg {
	namespace components {
		struct player : public entity_component
		{
			player(const int id, const std::string name, ::position position, ::scale scale, const sf::Sprite sprite) : entity_component(id, name, position, scale, sprite)
			{
			};
		};
	}
}