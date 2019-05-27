#pragma once
#include "SFML/System/Vector2.hpp"
#include "Sprite.hpp"

class Tile final : public sf::Drawable
{
public:
	Tile(unsigned int column, unsigned int row, sf::Vector2u size, Sprite sprite);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	unsigned int column_;
	unsigned int row_;
	sf::Vector2u size_;
	Sprite sprite_;
};

