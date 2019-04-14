#pragma once

#include <vector>

#include "map_layer.hpp"
#include "tmx_object_layer.hpp"
#include "map_object.hpp"

class MapObjectLayer :
	public MapLayer
{
public:
	MapObjectLayer(const int id, const std::string name, std::vector<MapObject> objects);
	~MapObjectLayer();

	int id;
	std::string name;

	std::vector<MapObject> objects;
};