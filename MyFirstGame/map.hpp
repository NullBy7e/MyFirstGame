#pragma once

#include <array>

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
			Map(
				std::vector<TmxTileset> map_tilesets,
				std::vector<TmxTileLayer> map_tile_layers,
				std::vector<TmxObjectLayer> map_object_layers,

				std::string version,
				std::string tiled_version,
				std::string orientation,
				std::string render_order,

				int width,
				int height,
				int tile_width,
				int tile_height,
				int pixel_width,
				int pixel_height
			);

			~Map();

			void loadSprites(TextureManager& texmgr);
			void loadObjects();

			void setPlayerData(PlayerData player_data);

			sf::Vector2f getEntityPosition(unsigned int entity);
			sf::Vector2f getPlayerPosition();
			sf::Vector2f getDimensions();

			const entt::view<PositionComponent, SpriteComponent> getEntities();

			sf::Sprite getSpriteByTileId(int tile_id);

			EntityManager& getEntityManager();
			Map& getRef();

			const std::map<std::pair<float, float>, std::vector<int>> getMappings(float begin_x, float begin_y, float end_y, float end_x);
		private:
			EntityManager entmgr;
			std::map<std::pair<float, float>, std::vector<int>> mappings;
		};
	}
}