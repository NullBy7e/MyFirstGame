#include "map_manager.hpp"
#include "texture_manager.hpp"
#include "entity_manager.hpp"

namespace mfg {
	namespace managers
	{
		static map_manager* instance;

		map_manager::map_manager()
		{
			instance = this;
		}

		TmxMap* map_manager::loadMap(int id)
		{
			auto map = getMap(id);

			auto texmgr = texture_manager::getInstance();
			auto entmgr = entity_manager::getInstance();

			auto player = entmgr->getPlayer();

			/* iterate through each tileset */
			for (int i = 0; i < map->tilesets.size(); i++)
			{
				auto tileset = map->tilesets[i];
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

						map->sprites[tn] = sprite;
					}
				}
			}

			/* object layers */
			for (auto& layer : map->object_layers)
			{
				for (auto& object : layer.objects)
				{
					auto new_sprite = sf::Sprite(map->sprites[object.gid]);

					/* load player texture into new_sprite here to prevent scale/sizing conflicts */
					if (object.name == "player_spawn" && object.type == "player")
					{
						auto tex = texmgr->get("player", "../../textures/sprites/player/knight_f_run_anim_f1.png");
						new_sprite.setTexture(tex.get(), true);
					}

					sf::Vector2f targetSize(object.width, object.height);

					auto bounds = new_sprite.getLocalBounds();

					float x_scale = targetSize.x / bounds.width;
					float y_scale = targetSize.y / bounds.height;

					auto x_pos = object.x;
					auto y_pos = object.y - object.height;

					/* check flips */
					if (object.flipped_horizontally)
					{
						x_pos = object.x + object.width;
					}

					auto entities = entmgr->getEntities();
					auto entity = entities->create();

					if (object.name == "player_spawn" && object.type == "player")
					{
						entity = player;
						entities->assign<mfg::components::map>(entity, mfg::components::map{ id });

						map->player_spawned = true;
					}

					if (object.type == "enemy")
					{
						entities->assign<enemy>(entity);
					}

					entities->assign<position>(entity, x_pos, y_pos);
					entities->assign<scale>(entity, x_scale, y_scale);
					entities->assign<sprite>(entity, new_sprite);
				}
			}

			currentMap.reset(map);
			return map;
		}

		int mfg::managers::map_manager::addMap(TmxMap map)
		{
			maps.push_back(std::make_unique<TmxMap>(map));
			return maps.size() - 1;
		}

		TmxMap* mfg::managers::map_manager::getMap(int id)
		{
			return maps[id].get();
		}

		TmxMap* mfg::managers::map_manager::getCurrentMap()
		{
			return currentMap.get();
		}

		map_manager * map_manager::getInstance()
		{
			return instance;
		}
	}
}