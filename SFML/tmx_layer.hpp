#pragma once

#include <string>

class TmxLayer
{
public:
	TmxLayer() {};
	virtual ~TmxLayer() {};

	TmxLayer(const int id, const std::string name, const int width, const int height);

	int id;
	std::string name;
	int width;
	int height;
};