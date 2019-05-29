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

	const auto x_pos = (column_ * size_.x) + size_.x / 2;
	const auto y_pos = (row_ * size_.y) + size_.y / 2;

	sprite.setPosition(x_pos, y_pos);

	const auto scale = sf::Vector2f{ (static_cast<float>(size_.x) / static_cast<float>(sprite_.get_tile_set().size_.x)), (static_cast<float>(size_.y) / static_cast<float>(sprite_.get_tile_set().size_.y)) };
	sprite.setScale(scale.x, scale.y);
	sprite.setRotation(sprite_.get_rotation());
	sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);

	target.draw(sprite);
}
