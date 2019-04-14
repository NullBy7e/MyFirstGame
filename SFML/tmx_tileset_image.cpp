#include "tmx_tileset_image.hpp"

TmxTilesetImage::TmxTilesetImage()
{
}

TmxTilesetImage::TmxTilesetImage(const std::string image_source, const int image_width, const int image_height)
{
	this->image_source = image_source;
	this->image_width = image_width;
	this->image_height = image_height;
}

TmxTilesetImage::~TmxTilesetImage()
{
}