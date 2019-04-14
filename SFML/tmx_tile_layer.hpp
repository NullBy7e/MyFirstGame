#pragma once

#include "tmx_layer.hpp"

class TmxTileLayer :
	public TmxLayer
{
public:
	TmxTileLayer(const int id, const std::string name, const int width, const int height, const std::string csvData);
	~TmxTileLayer();

	std::string csvData;
};