#include "MapEditorUi.hpp"

#include "../../helpers/MathHelper.hpp"
#include "../../map/MapEditor.hpp"
#include <imgui_stdlib.h>

#include "imgui-SFML.h"
#include <array>

MapEditorUi::MapEditorUi(MapEditor& map_editor) : mapEditor_(map_editor)
{
}

void MapEditorUi::initialize_ui_elements(Window& window)
{
	uiElements_.push_back(std::make_unique<Tilepicker>(
		mapEditor_.get_tilesets(),
		256,
		640,
		static_cast<float>(window.get().getSize().x - 256),
		0));

	uiElements_[uiElements_.size()-1]->connect_callback(this);
}

void MapEditorUi::draw_ui_elements()
{
	for(auto& element : uiElements_)
	{
		element->draw();
	}
}

void MapEditorUi::render(Window& window)
{
	if (uiElements_.empty())
		initialize_ui_elements(window);

	draw_ui_elements();

	//ImGui::Begin("Map Editor");

	//if (ImGui::BeginTabBar("TabItems"))
	//{
	//	if (ImGui::BeginTabItem("Properties", &propertiesTabEnabled_))
	//	{
	//		map_name_text_input();
	//		map_desc_text_input();

	//		ImGui::EndTabItem();
	//	}

	//	if (ImGui::BeginTabItem("Tilesets", &tilesetsTabEnabled_))
	//	{
	//		tileset_combo();
	//		tileset_info();
	//		tileset_sprites();

	//		ImGui::EndTabItem();
	//	}

	//	ImGui::EndTabBar();
	//}

	//ImGui::End();

	// draws the selected sprite (if any) next to the mouse cursor.
	selected_sprite();
}

MapEditor& MapEditorUi::get_map_editor() const
{
	return mapEditor_;
}

bool MapEditorUi::is_mouse_inside() const
{
	for(auto& element : uiElements_)
	{
		if (element->is_mouse_inside())
			return true;
	}

	return false;
}

void MapEditorUi::cb_tilepicker_sprite_selected(TileSet& tileset, unsigned sprite_index)
{
	mapEditor_.set_selected_sprite(tileset, sprite_index);
}

void MapEditorUi::map_desc_text_input() const
{
	const auto label = "Map description";
	const auto hint = "Enter a description.";

	ImGui::InputTextMultiline(label, &mapEditor_.get_map_desc());
}

void MapEditorUi::map_name_text_input() const
{
	const auto label = "Map name";
	const auto hint = "Enter the name of the map.";

	ImGui::InputTextWithHint(label, hint, &mapEditor_.get_map_name());
}

void MapEditorUi::selected_sprite() const
{
	// no need to draw the selected sprite if the mouse is inside any of the ui elements.
	if (is_mouse_inside())
		return;

	const auto selected_sprite = mapEditor_.get_selected_sprite();
	if (!selected_sprite)
		return;

	const auto mouse = ImGui::GetMousePos();
	ImGui::SetNextWindowPos({mouse.x + 10, mouse.y});

	if (ImGui::Begin("selectedSprite", nullptr,
	                 ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize))
	{
		const auto radians = MathHelper::DegreesToRadians(selected_sprite->get_rotation());
		auto uvs = selected_sprite->get_uvs();

		ImGui::ImageQuad(
			reinterpret_cast<void*>(selected_sprite->get_sprite().getTexture()->getNativeHandle()),
			{64, 64},
			radians,
			uvs[0],
			uvs[1],
			uvs[2],
			uvs[3]
		);
	}

	ImGui::End();
}

ImVec2 MapEditorUi::get_uv0_coord(const sf::Vector2f& tex_size, const sf::Vector2f& tex_rect)
{
	return ImVec2(tex_rect.x / tex_size.x, tex_rect.y / tex_size.y);
}

ImVec2 MapEditorUi::get_uv1_coord(const sf::Vector2f& tex_size, const sf::Vector2f& tex_rect,
                                  const sf::Vector2f spr_size)
{
	return ImVec2((tex_rect.x + spr_size.x) / tex_size.x, (tex_rect.y + spr_size.y) / tex_size.y);
}
