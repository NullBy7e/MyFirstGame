#pragma once

#include <string>

class MapLayer
{
public:

	MapLayer() {};
	virtual ~MapLayer() {};

	MapLayer(const std::string name, const int width, const int height);

	std::string name;
	int width;
	int height;
};