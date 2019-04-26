#pragma once

#include "tmx/tmx_map.hpp"

#include "managers/texture_manager.hpp"
#include "managers/entity_manager.hpp"

#include "player_data.hpp"

using namespace mfg::managers;

namespace mfg
{
	namespace core
	{
		class Map : public TmxMap
		{
		public:
			Map();
			~Map();

			void loadSprites(TextureManager * texmgr);
			void loadObjects();

			void setPlayerData(PlayerData player_data);

			sf::Vector2f getEntityPosition(unsigned int entity);
			sf::Vector2f getPlayerPosition();
			sf::Vector2f getDimensions();

			entt::view<PositionComponent, SpriteComponent> getEntities();

			EntityManager& getEntityManager();
		private:
			EntityManager entmgr;
		};
	}
}