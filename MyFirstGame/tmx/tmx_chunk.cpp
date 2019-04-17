#include "tmx_chunk.hpp"

TmxChunk::TmxChunk(float x, float y, int width, int height, std::vector<TmxTile> tiles)
{
	this->x = x;
	this->y = y;

	this->width = width;
	this->height = height;

	this->tiles = tiles;
}

TmxChunk::~TmxChunk()
{
}