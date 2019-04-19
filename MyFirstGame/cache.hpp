#pragma once

#include <SFML/Graphics.hpp>

#include "entt/entt.hpp"
#include "texture_loader.hpp"

using texture_cache = entt::resource_cache<sf::Texture>;
texture_cache textures{};