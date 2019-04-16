#include "tmx_object_property.hpp"

TmxObjectProperty::TmxObjectProperty(const std::string name, const std::string type, const std::string value)
{
	this->name = name;
	this->type = type;
	this->value = value;
}

TmxObjectProperty::~TmxObjectProperty()
{
}