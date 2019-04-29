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

#pragma once

#include <map>
#include <vector>

#include "tmx_tileset.hpp"
#include "tmx_tile_layer.hpp"
#include "tmx_object_layer.hpp"

class TmxMap
{
public:
	TmxMap() = default;
	TmxMap(
		std::map<std::string, std::string> map_properties,
		std::vector<TmxTileset>            map_tilesets,
		std::vector<TmxTileLayer>          map_tile_layers,
		std::vector<TmxObjectLayer>        map_object_layers
	);

	static int cStrToInt(const char* x);

	std::string version;
	std::string tiled_version;
	std::string orientation;
	std::string render_order;

	int width{};
	int height{};
	int tile_width{};
	int tile_height{};
	int pixel_width{};
	int pixel_height{};

	std::vector<TmxTileset> tilesets;

	std::vector<TmxTileLayer>   tile_layers;
	std::vector<TmxObjectLayer> object_layers;

	/* array that maps tile number to sprite (contains all sprites from the tileset and the number that
	 * Tiled would normally assign to it */
	std::map<int, sf::Sprite> sprites;

	bool player_spawned{};
};
