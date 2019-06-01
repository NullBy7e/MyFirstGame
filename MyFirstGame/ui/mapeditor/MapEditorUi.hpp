#pragma once
#include <imgui.h>
#include "../../core/Window.hpp"
#include "Tilepicker.hpp"
#include "UiElementCallbackInterface.hpp"

class MapEditor;

// ReSharper disable once CppPolymorphicClassWithNonVirtualPublicDestructor
/**
 * \brief The user interface for the map editor.
 */
class MapEditorUi final : UiElementCallbackInterface
{
public:
	explicit MapEditorUi(MapEditor& map_editor);
	void initialize_ui_elements(Window& window);
	void draw_ui_elements();
	void render(Window& window);
	MapEditor& get_map_editor() const;

	bool is_mouse_inside() const;

	void cb_tilepicker_sprite_selected(TileSet& tileset, unsigned int sprite_index) override;
private:
	void map_name_text_input() const;
	void map_desc_text_input() const;

	void selected_sprite() const;

	static ImVec2 get_uv0_coord(const sf::Vector2f& tex_size, const sf::Vector2f& tex_rect);
	static ImVec2 get_uv1_coord(const sf::Vector2f& tex_size, const sf::Vector2f& tex_rect, sf::Vector2f spr_size);

	bool propertiesTabEnabled_ = true;
	MapEditor& mapEditor_;

	std::vector<std::unique_ptr<UiElement>> uiElements_;
};
