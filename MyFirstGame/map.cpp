#include "map.hpp"

namespace mfg
{
	namespace core
	{
		Map::Map(
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
			int pixel_height)
		{
			DEBUG_MSG("CTOR " << "	 [" << std::addressof(*this) << "]	Map");

			tilesets = map_tilesets;
			tile_layers = map_tile_layers;
			object_layers = map_object_layers;

			this->version = version;
			this->tiled_version = tiled_version;
			this->orientation = orientation;
			this->render_order = render_order;
			this->width = width;
			this->height = height;
			this->tile_width = tile_width;
			this->tile_height = tile_height;
			this->pixel_width = pixel_width;
			this->pixel_height = pixel_height;

			for (auto layer : tile_layers)
			{
				for (int col = 0; col < width; ++col)
				{
					for (int row = 0; row < height; ++row)
					{
						auto x = col * tile_width;
						auto y = row * tile_height;

						/* the tile id */
						auto tile_id = layer.tiles[(row * width) + col].id;

						/* map x and y to a tile id */
						mappings[{x, y}].push_back(tile_id);
					}
				}
			}
		}

		Map::~Map()
		{
			DEBUG_MSG("DTOR " << "	 [" << std::addressof(*this) << "]	Map");
		}

		void Map::loadSprites(TextureManager& texmgr)
		{
			/* iterate through each tileset */
			for (int i = 0; i < tilesets.size(); i++)
			{
				auto tileset = tilesets[i];
				auto tex = texmgr.get(tileset.name, tileset.image.image_source);

				/* iterate through each row */
				for (int row = 0; row < (tileset.tile_count / tileset.columns); ++row)
				{
					/* indicates at which Y pos this row starts */
					auto row_start_y_pos = row * tileset.tile_height;

					/* iterate through each column */
					for (int col = 0; col < tileset.columns; col++)
					{
						/* the tile number used by Tiled */
						auto tn = (tileset.first_gid + col) + (row * tileset.columns);

						/* X & Y pos calculation */
						auto xpos = col * tileset.tile_width;
						auto ypos = row_start_y_pos;

						/* Make a new sprite */
						sf::Sprite sprite(tex.get(), sf::IntRect(xpos, ypos, tileset.tile_width, tileset.tile_height));

						sprites[tn] = sprite;
					}
				}
			}
		}

		void Map::loadObjects()
		{
			auto& entities = entmgr.getEntities();
			entmgr.setPlayer(entities.create());

			/* object layers */
			for (auto& layer : object_layers)
			{
				for (auto& object : layer.objects)
				{
					if (object.type == "spawn")
					{
						auto y_pos = object.y;

						/* if an object in Tiled does not have a sprite, then the Y pos starts at the bottom
						   so here we adjust accordingly */
						if (object.gid == -1)
							y_pos += object.height;

						auto actor = entmgr.createActor
						(
							object.name,
							300,
							object.flipped_horizontally,
							object.width,
							object.height,
							sprites[object.gid],
							sf::Vector2f(object.x, y_pos)
						);

						if (object.name == "player")
							entmgr.setPlayer(actor);
					}
				}
			}
		}

		void Map::setPlayerData(PlayerData player_data)
		{
			auto& entities = entmgr.getEntities();

			entities.assign_or_replace<ActorComponent>(entmgr.getPlayer(), std::get<ActorComponent>(player_data));
			entities.assign_or_replace<AnimationComponent>(entmgr.getPlayer(), std::get<AnimationComponent>(player_data));
			entities.assign_or_replace<HealthComponent>(entmgr.getPlayer(), std::get<HealthComponent>(player_data));
			entities.assign_or_replace<SpriteComponent>(entmgr.getPlayer(), std::get<SpriteComponent>(player_data));
		}

		sf::Vector2f Map::getEntityPosition(unsigned int entity)
		{
			return entmgr.getEntities().get<PositionComponent>(entity).getPosition();
		}

		sf::Vector2f Map::getPlayerPosition()
		{
			return getEntityPosition(entmgr.getPlayer());
		}

		sf::Vector2f Map::getDimensions()
		{
			return sf::Vector2f(pixel_width, pixel_height);
		}

		const entt::view<PositionComponent, SpriteComponent> Map::getEntities()
		{
			return entmgr.getEntities().view<PositionComponent, SpriteComponent>();
		}

		sf::Sprite Map::getSpriteByTileId(int tile_id)
		{
			return sprites[tile_id];
		}

		EntityManager& Map::getEntityManager()
		{
			return entmgr;
		}

		Map& Map::getRef()
		{
			return *this;
		}

		const std::map<std::pair<float, float>, std::vector<int>> Map::getMappings(float begin_x, float begin_y, float end_y, float end_x)
		{
			std::map<std::pair<float, float>, std::vector<int>> new_mappings;

			std::copy_if(mappings.begin(), mappings.end(), std::inserter(new_mappings, new_mappings.begin()), [begin_x, begin_y, end_y, end_x](const auto m)
			{
				return m.first.first >= begin_x && m.first.first <= end_x && m.first.second >= begin_y && m.first.second <= end_y;
			});

			return new_mappings;
		}
	}
}