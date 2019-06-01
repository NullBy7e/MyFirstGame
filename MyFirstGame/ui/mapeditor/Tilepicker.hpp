#pragma once

#include "UiElement.hpp"
#include "Tilepicker.hpp"
#include "../../map/TileSet.hpp"

class Tilepicker final : public UiElement
{
public:
	Tilepicker(std::vector<TileSet>* tilesets, const float width, const float height, const float x, const float y);
	
	void draw() override;
	
	void tileset_combo();
	void tileset_sprites();
private:
	int tilesetComboSelectedItemIndex_ = -1;

	std::vector<TileSet>* tilesets_;
};

