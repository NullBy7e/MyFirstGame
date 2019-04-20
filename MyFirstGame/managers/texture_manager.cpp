#include "texture_manager.hpp"

namespace mfg
{
	namespace managers
	{
		static texture_manager* instance;

		texture_manager::texture_manager()
		{
			instance = this;
		}

		entt::resource_handle<sf::Texture> texture_manager::get(const std::string texture_name, const std::string texture_path)
		{
			return textures.load<texture_loader>(entt::hashed_string::to_value(texture_name.c_str()), texture_path);
		}

		texture_manager * texture_manager::getInstance()
		{
			return instance;
		}
	}
}