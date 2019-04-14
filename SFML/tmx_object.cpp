#include "tmx_object.hpp"

TmxObject::TmxObject(const int id,
	const std::string name,
	const std::string type,
	const float x,
	const float y,
	const int width,
	const int height,
	const int gid,
	const bool flipped_horizontally,
	const bool flipped_vertically,
	const bool flipped_diagonally)
{
	this->id = id;
	this->name = name;
	this->type = type;
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->gid = gid;
	this->flipped_horizontally = flipped_horizontally;
	this->flipped_vertically = flipped_vertically;
	this->flipped_diagonally = flipped_diagonally;
}

TmxObject::~TmxObject()
{
}