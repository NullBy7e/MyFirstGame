/*
MIT License

Copyright (c) 2019 Youri de Mooij

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "map_manager.hpp"
#include "texture_manager.hpp"
#include "entity_manager.hpp"

namespace mfg {
	namespace managers
	{
		TmxMap* map_manager::loadMap(int id, texture_manager* texmgr, entity_manager* entmgr)
		{
			auto map = getMap(id);

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
					auto& entities = entmgr->getEntities();

					if (object.name == "player_spawn" && object.type == "player")
					{
						auto& player_entity = entities.get<mfg::components::entity>(entmgr->getPlayer());

						player_entity.x = object.x;
						player_entity.y = object.y - player_entity.sprite.getLocalBounds().height;

						map->player_spawned = true;
						continue;
					}

					sf::Vector2f targetSize(object.width, object.height);
					auto new_sprite = sf::Sprite(map->sprites[object.gid]);
					new_sprite.setOrigin({ new_sprite.getLocalBounds().width, 0 });

					auto bounds = new_sprite.getLocalBounds();

					float x_scale = targetSize.x / bounds.width;
					float y_scale = targetSize.y / bounds.height;

					auto entity = entities.create();

					new_sprite.setScale(x_scale, y_scale);
					new_sprite.setRotation(object.rotation);

					auto x_pos = object.x;
					auto y_pos = object.y - object.height;

					if (object.flipped_horizontally)
					{
						x_pos = object.x + object.width;
					}

					if (!entities.has<mfg::components::entity>(entity))
					{
						entities.assign<mfg::components::entity>(entity, x_pos, y_pos, object.width, object.height, x_scale, y_scale, object.rotation, object.flipped_horizontally, new_sprite);
					}

					if (!entities.has<mfg::components::map>(entity))
					{
						entities.assign<mfg::components::map>(entity, mfg::components::map{ id });
					}
				}
			}

			currentMap.reset(map);
			return map;
		}

		int map_manager::addMap(TmxMap* map)
		{
			maps.push_back(std::unique_ptr<TmxMap>(map));
			return maps.size() - 1;
		}

		TmxMap* map_manager::getMap(int id)
		{
			return maps[id].get();
		}

		TmxMap* map_manager::getCurrentMap()
		{
			return currentMap.get();
		}
	}
}