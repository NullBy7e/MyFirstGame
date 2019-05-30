#include "Sprite.hpp"
#include <array>

Sprite::Sprite(TileSet& tile_set, const int sprite_index) : tileSet_(tile_set), spriteIndex_(sprite_index)
{
	auto sprite = tile_set.get_sprite(sprite_index);

	const auto tex_size = sf::Vector2f(static_cast<float>(sprite.getTexture()->getSize().x), static_cast<float>(sprite.getTexture()->getSize().y));
	const auto tex_rect = sf::Vector2f(static_cast<float>(sprite.getTextureRect().left), static_cast<float>(sprite.getTextureRect().top));
	const auto spr_size = sf::Vector2f(static_cast<float>(sprite.getTextureRect().width), static_cast<float>(sprite.getTextureRect().height));

	uv0_ = ImVec2(tex_rect.x / tex_size.x, tex_rect.y / tex_size.y);
	uv1_ = ImVec2((tex_rect.x + spr_size.x) / tex_size.x, (tex_rect.y + spr_size.y) / tex_size.y);

	rotation_ = sprite.getRotation();
}

TileSet& Sprite::get_tile_set() const
{
	return tileSet_;
}

int Sprite::get_sprite_index() const
{
	return spriteIndex_;
}

sf::Sprite Sprite::get_sprite() const
{
	return tileSet_.get_sprite(spriteIndex_);
}

ImVec2 Sprite::get_uv0_coord() const
{
	return uv0_;
}

ImVec2 Sprite::get_uv1_coord() const
{
	return uv1_;
}

std::array<ImVec2, 4> Sprite::get_uvs() const
{
	return 	
	{
		ImVec2(uv0_.x, uv0_.y), //top left
		ImVec2(uv1_.x, uv0_.y), //top right
		ImVec2(uv1_.x, uv1_.y), //bottom right
		ImVec2(uv0_.x, uv1_.y)  //bottom left
	};
}

void Sprite::rotate(const float angle)
{
	rotation_ += angle;
}

void Sprite::set_rotation(const float angle)
{
	rotation_ = angle;
}

float Sprite::get_rotation() const
{
	return rotation_;
}

