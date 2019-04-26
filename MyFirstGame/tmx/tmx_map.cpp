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

#include "tmx_map.hpp"

TmxMap::TmxMap() {};

TmxMap::TmxMap(
	std::map<std::string, std::string> map_properties,
	std::vector<TmxTileset> map_tilesets,
	std::vector<TmxTileLayer> map_tile_layers,
	std::vector<TmxObjectLayer> map_object_layers)
	:
	tilesets(map_tilesets),
	tile_layers(map_tile_layers),
	object_layers(map_object_layers)
{
	version = map_properties["version"];
	tiled_version = map_properties["tiledversion"];
	orientation = map_properties["orientation"];
	render_order = map_properties["renderorder"];

	width = cStrToInt(map_properties["width"].c_str());
	height = cStrToInt(map_properties["height"].c_str());

	tile_width = cStrToInt(map_properties["tilewidth"].c_str());
	tile_height = cStrToInt(map_properties["tileheight"].c_str());

	pixel_width = width * tile_width;
	pixel_height = height * tile_height;
}

int TmxMap::cStrToInt(const char * x)
{
	int y;
	std::stringstream(x) >> y;

	return y;
}