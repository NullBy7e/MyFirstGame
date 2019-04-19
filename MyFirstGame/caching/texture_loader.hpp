#pragma once

#include <SFML/Graphics.hpp>

#include "entt/entt.hpp"

namespace mfg
{
	namespace caching
	{
		struct texture_loader : entt::resource_loader<texture_loader, sf::Texture> {
			std::shared_ptr<sf::Texture> load(std::string texture_path) const {
				sf::Texture tex;
				tex.loadFromFile(texture_path);

				return std::shared_ptr<sf::Texture>(new sf::Texture{ tex });
			}
		};
	}
}