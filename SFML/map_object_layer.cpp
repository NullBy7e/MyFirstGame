#include "map_object_layer.hpp"

MapObjectLayer::MapObjectLayer(const int id, const std::string name, std::vector<MapObject> objects)
{
	this->id = id;
	this->name = name;
	this->objects = objects;
}

MapObjectLayer::~MapObjectLayer()
{
}