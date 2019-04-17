#pragma once

#include <vector>

#include "tmx_tile.hpp"

class TmxChunk
{
public:
	TmxChunk(float x, float y, int width, int height, std::vector<TmxTile> tiles);
	~TmxChunk();

	float x;
	float y;

	int width;
	int height;

	std::vector<TmxTile> tiles;
};