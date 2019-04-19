#pragma once

#include <SFML/Graphics.hpp>

#include "entt/entt.hpp"
#include "texture_loader.hpp"

namespace mfg
{
	namespace caching
	{
		using texture_cache = entt::resource_cache<sf::Texture>;
	}
}