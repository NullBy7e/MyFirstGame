#include "tmx_tileset.hpp"

TmxTileset::TmxTileset()
{
}

TmxTileset::TmxTileset(const int first_gid, const std::string name, const int tile_width, const int tile_height,
	const int tile_count,
	const int columns,
	const std::string image_source,
	const int image_width,
	const int image_height)
{
	this->first_gid = first_gid;
	this->name = name;
	this->tile_width = tile_width;
	this->tile_height = tile_height;
	this->tile_count = tile_count;
	this->columns = columns;

	image = TmxTilesetImage(image_source, image_width, image_height);
}

TmxTileset::~TmxTileset()
{
}