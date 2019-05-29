#pragma once
#include "TileSet.hpp"
#include <imgui.h>

class Sprite
{
public:
	Sprite(TileSet& tile_set, const int sprite_index);

	TileSet& get_tile_set() const;
	int get_sprite_index() const;
	sf::Sprite get_sprite() const;

	ImVec2 get_uv0_coord() const;
	ImVec2 get_uv1_coord() const;

	std::array<ImVec2, 4> get_uvs() const;

	void rotate(float angle);
	void set_rotation(float angle);

	float get_rotation() const;
private:
	TileSet& tileSet_;
	int spriteIndex_;

	ImVec2 uv0_, uv1_;

	float rotation_;
};
