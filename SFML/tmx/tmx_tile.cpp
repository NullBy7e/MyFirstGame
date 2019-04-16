#include "tmx_tile.hpp"

TmxTile::TmxTile(int tile_id)
{
	this->id = tile_id;
}

TmxTile::~TmxTile()
{
}

void TmxTile::setSprite(sf::Sprite sprite)
{
	this->sprite = sf::Sprite(sprite);
}

sf::Sprite& TmxTile::getSprite()
{
	return this->sprite;
}