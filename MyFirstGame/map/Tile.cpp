#include "Tile.hpp"
#include "../external/SFML-2.5.1/x86/include/SFML/Graphics/RenderTarget.hpp"

Tile::Tile(const unsigned int column, const unsigned int row, const sf::Vector2u size, const Sprite sprite)
	:
	column_(column),
	row_(row),
	size_(size),
	sprite_(sprite)
{
}

void Tile::draw(sf::RenderTarget& target, const sf::RenderStates states) const
{
	auto sprite = sprite_.get_sprite();
	sprite.setPosition(column_ * size_.x, row_ * size_.y);

	const auto scale = sf::Vector2u{ (size_.x / sprite_.get_tile_set().size_.x), (size_.y / sprite_.get_tile_set().size_.y) };
	sprite.setScale(scale.x, scale.y);
	
	target.draw(sprite);
}
