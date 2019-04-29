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

#include <filesystem>

#include <map>
#include <vector>

#include "tinyxml2.hpp"

#include "tmx_map.hpp"
#include "tmx_tileset.hpp"
#include "tmx_tile_layer.hpp"
#include "tmx_object_layer.hpp"

using namespace tinyxml2;

class TmxParser
{
public:
	TmxParser() = default;

	TmxMap parse(const std::string&) const;

	static int cStrToInt(const char* x);

	static unsigned int cStrToUInt(const char* x);

	static float cStrToFloat(const char* x);

private:
	const std::string target_tiled_version_ = "1.2.3";

	std::map<std::string, std::string> getMapElementProperties(const XMLElement&) const;
	std::vector<TmxTileset>            getMapTilesets(const XMLElement&         ) const;
	std::vector<TmxTileLayer>          getMapTileLayers(const XMLElement&       ) const;
	static std::vector<TmxObjectLayer> getMapObjectLayers(const XMLElement&     );
};
