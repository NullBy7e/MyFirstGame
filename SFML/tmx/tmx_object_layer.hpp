#pragma once

#include <vector>

#include "tmx_layer.hpp"
#include "tmx_object.hpp"

class TmxObjectLayer :
	public TmxLayer
{
public:
	TmxObjectLayer(const int id, const std::string name);
	~TmxObjectLayer();

	std::vector<TmxObject> objects;
};