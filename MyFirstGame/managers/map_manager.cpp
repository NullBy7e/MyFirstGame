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

namespace mfg
{
	namespace managers
	{
		Map& MapManager::loadMap(const int id, TextureManager& texmgr)
		{
			auto& map = getMap(id);

			map.loadSprites(texmgr);
			map.loadObjects();

			current_map_ = id;
			return map;
		}

		int MapManager::addMap(const TmxMap map)
		{
			const auto new_map = new Map
			(
				map.tilesets,
				map.tile_layers,
				map.object_layers,
				map.version,
				map.tiled_version,
				map.orientation,
				map.render_order,
				map.width,
				map.height,
				map.tile_width,
				map.tile_height,
				map.pixel_width,
				map.pixel_height
			);

			maps_.push_back(std::unique_ptr<Map>(new_map));
			return maps_.size() - 1;
		}

		Map& MapManager::getMap(const int id)
		{
			return *maps_[id];
		}

		Map& MapManager::getCurrentMap()
		{
			return *maps_[current_map_];
		}
	}
}
