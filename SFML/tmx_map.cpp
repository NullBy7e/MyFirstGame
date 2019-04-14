#include "tmx_map.hpp"

TmxMap::TmxMap(std::map<std::string, std::string> map_properties, std::vector<TmxTileset> map_tilesets, std::vector<TmxTileLayer> map_tile_layers, std::vector<TmxObjectLayer> map_object_layers)
{
	this->version = map_properties["version"];
	this->tiled_version = map_properties["tiledversion"];
	this->orientation = map_properties["orientation"];
	this->render_order = map_properties["renderorder"];

	this->width = cStrToInt(map_properties["width"].c_str());
	this->height = cStrToInt(map_properties["height"].c_str());
	this->tile_width = cStrToInt(map_properties["tilewidth"].c_str());
	this->tile_height = cStrToInt(map_properties["tileheight"].c_str());

	this->tilesets = map_tilesets;
	this->tile_layers = map_tile_layers;
	this->object_layers = map_object_layers;
}

TmxMap::~TmxMap()
{
}