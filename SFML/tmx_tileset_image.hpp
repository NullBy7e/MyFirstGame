#pragma once

#include <string>
#include <iostream>

#include <SFML/Graphics.hpp>

class TmxTilesetImage
{
public:
	TmxTilesetImage();
	TmxTilesetImage(const std::string image_source, const int image_width, const int image_height);
	~TmxTilesetImage();

	std::string image_source;
	int image_width;
	int image_height;
};