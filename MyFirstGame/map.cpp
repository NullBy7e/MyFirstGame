#include "map.hpp"

namespace mfg
{
	namespace core
	{
		Map::Map()
		{
			DEBUG_MSG("CTOR " << "	 [" << std::addressof(*this) << "]	Map");
		}

		Map::~Map()
		{
			DEBUG_MSG("DTOR " << "	 [" << std::addressof(*this) << "]	Map");
		}

		void Map::loadSprites(TextureManager* texmgr)
		{
			/* iterate through each tileset */
			for (int i = 0; i < tilesets.size(); i++)
			{
				auto tileset = tilesets[i];
				auto tex = texmgr->get(tileset.name, tileset.image.image_source);

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
					auto is_player = object.name == "player";

					if (object.type == "spawn")
					{
						auto entity = entities.create();

						if (is_player)
						{
							entity = entmgr.getPlayer();
							player_spawned = true;
						}

						auto y_pos = object.y;

						/* if an object in Tiled does not have a sprite, then the Y pos starts at the bottom
						   so here we adjust accordingly */
						if (object.gid == -1)
							y_pos += object.height;

						entities.assign<PositionComponent>(entity, object.x, y_pos);

						/* the player has a custom sprite */
						if (!is_player)
						{
							entities.assign<ActorComponent>(entity, object.name);
							entities.assign<AnimationComponent>(entity);
							entities.assign<HealthComponent>(entity, 300);
							entities.assign<SpriteComponent>(entity, SpriteComponent(object.flipped_horizontally, object.width, object.height, sprites[object.gid]));
						}
					}
				}
			}
		}

		void Map::setPlayerData(PlayerData player_data)
		{
			auto& entities = entmgr.getEntities();

			entities.assign<ActorComponent>(entmgr.getPlayer(), player_data.actor);
			entities.assign<AnimationComponent>(entmgr.getPlayer(), player_data.animation);
			entities.assign<HealthComponent>(entmgr.getPlayer(), player_data.health);
			entities.assign<SpriteComponent>(entmgr.getPlayer(), player_data.sprite);
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

		entt::view<PositionComponent, SpriteComponent> Map::getEntities()
		{
			return entmgr.getEntities().view<PositionComponent, SpriteComponent>();
		}

		EntityManager& Map::getEntityManager()
		{
			return entmgr;
		}
	}
}