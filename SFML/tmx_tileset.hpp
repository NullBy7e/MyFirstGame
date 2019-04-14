#pragma once

#include <string>
#include "tmx_tileset_image.hpp"

class TmxTileset
{
public:
	TmxTileset();

	TmxTileset(
		const int first_gid,
		const std::string name,
		const int tile_width,
		const int tile_height,
		const int tile_count,
		const int columns,
		const std::string image_source,
		const int image_width,
		const int image_height
	);
	~TmxTileset();

	int first_gid;
	std::string name;
	int tile_width;
	int tile_height;
	int tile_count;
	int columns;

	TmxTilesetImage image;
};