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

TmxMap::TmxMap(std::map<std::string, std::string> map_properties, std::vector<TmxTileset> map_tilesets, std::vector<TmxTileLayer> map_tile_layers, std::vector<TmxObjectLayer> map_object_layers)
{
	this->version = map_properties["version"];
	this->tiled_version = map_properties["tiledversion"];
	this->orientation = map_properties["orientation"];
	this->render_order = map_properties["renderorder"];

	this->width = cStrToInt(map_properties["width"].c_str());
	this->height = cStrToInt(map_properties["height"].c_str());

	this->tile_width = cStrToInt(map_properties["tilewidth"].c_str());
	this->tile_height = cStrToInt(map_properties["tileheight"].c_str());

	this->pixel_width = this->width * this->tile_width;
	this->pixel_height = this->height * this->tile_height;

	this->tilesets = map_tilesets;
	this->tile_layers = map_tile_layers;
	this->object_layers = map_object_layers;
}

TmxMap::~TmxMap()
{
}