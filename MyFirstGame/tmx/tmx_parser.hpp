/*
MIT License

Copyright (c) 2019 Youri de Mooij

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#pragma once

#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>

#include <filesystem>
#include <direct.h>

#include <map>
#include <vector>

#include "tinyxml2.hpp"

#include "tmx_map.hpp"
#include "tmx_tileset.hpp"
#include "tmx_layer.hpp"
#include "tmx_tile_layer.hpp"
#include "tmx_object_layer.hpp"

using namespace tinyxml2;

class TmxParser
{
public:
	TmxParser();

	TmxMap parse(const std::string&);

	int cStrToInt(const char * x);

	unsigned int cStrToUInt(const char * x);

	float cStrToFloat(const char * x);

private:
	const std::string target_tiled_version = "1.2.3";

	std::map<std::string, std::string> getMapElementProperties(const XMLElement&);
	std::vector<TmxTileset> getMapTilesets(const XMLElement&);
	std::vector<TmxTileLayer> getMapTileLayers(const XMLElement&);
	std::vector<TmxObjectLayer> getMapObjectLayers(const XMLElement&);
};