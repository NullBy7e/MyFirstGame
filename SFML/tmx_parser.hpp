#pragma once

#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>

#include <filesystem>
#include <direct.h>

#include <map>
#include <vector>

#include "tmx_map.hpp"
#include "tmx_tileset.hpp"
#include "tmx_layer.hpp"
#include "tmx_tile_layer.hpp"
#include "tmx_object_layer.hpp"

#include "tinyxml2/tinyxml2.h"

using namespace tinyxml2;

class TmxParser
{
public:
	TmxParser();
	~TmxParser();

	TmxMap parse(const std::string&);

	int cStrToInt(const char * x)
	{
		int y;
		std::stringstream(x) >> y;

		return y;
	}

	unsigned int cStrToUInt(const char * x)
	{
		unsigned int y;
		std::stringstream(x) >> y;

		return y;
	}

	float cStrToFloat(const char * x)
	{
		return strtof(x, 0);
	}

private:
	const std::string target_tiled_version = "1.2.3";

	std::map<std::string, std::string> getMapElementProperties(const XMLElement&);
	std::vector<TmxTileset> getMapTilesets(const XMLElement&);
	std::vector<TmxTileLayer> getMapTileLayers(const XMLElement&);
	std::vector<TmxObjectLayer> getMapObjectLayers(const XMLElement&);
};