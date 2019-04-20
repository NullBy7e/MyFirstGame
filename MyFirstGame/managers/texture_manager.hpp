#pragma once

#include "../caching/cache.hpp"

using namespace mfg::caching;

namespace mfg
{
	namespace managers
	{
		class texture_manager
		{
		public:
			texture_manager();

			entt::resource_handle<sf::Texture> get(const std::string texture_name, const std::string texture_path);

			static texture_manager* getInstance();
		private:
			texture_cache textures;
		};
	}
}