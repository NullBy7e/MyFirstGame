#include "map_layer.hpp"
#include "map_tile_layer.hpp"

MapTileLayer::MapTileLayer(std::vector<int> tiles_to_draw, const std::string name, const int width, const int height) : MapLayer(name, width, height)
{
	this->tiles_to_draw = tiles_to_draw;
}

MapTileLayer::~MapTileLayer()
{
}