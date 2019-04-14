#include "tmx_tile_layer.hpp"

TmxTileLayer::TmxTileLayer(const int id, const std::string name, const int width, const int height, const std::string csvData) : TmxLayer(id, name, width, height)
{
	this->csvData = csvData;
}

TmxTileLayer::~TmxTileLayer()
{
}