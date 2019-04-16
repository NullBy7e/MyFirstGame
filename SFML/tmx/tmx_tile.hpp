#pragma once

#include <SFML/Graphics.hpp>

class TmxTile
{
public:
	TmxTile(int tile_id);
	~TmxTile();

	int id;

	float x;
	float y;

	bool drawn;

	void setSprite(sf::Sprite sprite);
	sf::Sprite& getSprite();

private:
	sf::Sprite sprite;
};