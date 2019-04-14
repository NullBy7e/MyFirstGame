#include "tmx_layer.hpp"

TmxLayer::TmxLayer(const int id, const std::string name, const int width, const int height)
{
	this->id = id;
	this->name = name;
	this->width = width;
	this->height = height;
}