#pragma once

#include <vector>

#include "map_object_property.hpp"

class MapObject
{
public:
	MapObject(
		const int id,
		const std::string name,
		const std::string type,
		const float x,
		const float y,
		const int width,
		const int height,
		const int gid,
		const bool flipped_horizontally,
		const bool flipped_vertically,
		const bool flipped_diagonally);

	~MapObject();

	int id;
	std::string name;
	std::string type;
	float x;
	float y;
	int width;
	int height;
	int gid;

	bool flipped_horizontally;
	bool flipped_vertically;
	bool flipped_diagonally;

	std::vector<MapObjectProperty> properties;
};