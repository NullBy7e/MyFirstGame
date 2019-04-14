#pragma once

#include <string>

class MapObjectProperty
{
public:
	MapObjectProperty(const std::string name, const std::string type, const std::string value);
	~MapObjectProperty();

	std::string name;
	std::string type;
	std::string value;
};