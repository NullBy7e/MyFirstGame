#pragma once

#include <map>
#include <vector>
#include <sstream>

#include "tmx_tileset.hpp"
#include "tmx_layer.hpp"
#include "tmx_tile_layer.hpp"
#include "tmx_object_layer.hpp"

class TmxMap
{
public:
	TmxMap(
		std::map<std::string, std::string> map_properties,
		std::vector<TmxTileset> map_tilesets,
		std::vector<TmxTileLayer> map_tile_layers,
		std::vector<TmxObjectLayer> map_object_layers
	);
	~TmxMap();

	int cStrToInt(const char * x)
	{
		int y;
		std::stringstream(x) >> y;

		return y;
	}

	std::string version;
	std::string tiled_version;
	std::string orientation;
	std::string render_order;

	int width;
	int height;
	int tile_width;
	int tile_height;

	std::vector<TmxTileset> tilesets;

	std::vector<TmxTileLayer> tile_layers;
	std::vector<TmxObjectLayer> object_layers;
};