#include "map_object_property.hpp"

MapObjectProperty::MapObjectProperty(const std::string name, const std::string type, const std::string value)
{
	this->name = name;
	this->type = type;
	this->value = value;
}

MapObjectProperty::~MapObjectProperty()
{
}