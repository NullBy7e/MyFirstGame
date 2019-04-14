#pragma once

#include <vector>

#include "map_layer.hpp"

class MapTileLayer :
	public MapLayer
{
public:
	MapTileLayer(std::vector<int> tiles_to_draw, const std::string name, const int width, const int height);
	~MapTileLayer();

	std::vector<int> tiles_to_draw;
};