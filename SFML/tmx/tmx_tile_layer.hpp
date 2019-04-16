#pragma once

#include <vector>

#include "tmx_layer.hpp"
#include "tmx_tile.hpp"

class TmxTileLayer :
	public TmxLayer
{
public:
	TmxTileLayer(const int id, const std::string name, const int width, const int height, const std::vector<TmxTile> tiles);
	~TmxTileLayer();

	std::vector<TmxTile> tiles;
};