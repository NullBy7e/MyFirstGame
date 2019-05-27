#pragma once
#include <imgui.h>
#include "../map/Sprite.hpp"
#include <optional>

class MapEditor;

class MapEditorUi
{
public:
	explicit MapEditorUi(MapEditor& map_editor);
	void render();

private:
	void map_name_text_input() const;
	void map_desc_text_input() const;

	void tileset_combo();
	void tileset_info() const;
	void tileset_sprites() const;
	void selected_sprite() const;

	static ImVec2 get_uv0_coord(const sf::Vector2f& tex_size, const sf::Vector2f& tex_rect);
	static ImVec2 get_uv1_coord(const sf::Vector2f& tex_size, const sf::Vector2f& tex_rect, sf::Vector2f spr_size);

	int tilesetComboSelectedItemIndex_ = -1;

	bool propertiesTabEnabled_ = true;
	bool tilesetsTabEnabled_ = true;

	MapEditor& mapEditor_;
};