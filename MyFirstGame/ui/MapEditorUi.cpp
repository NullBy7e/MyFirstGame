#include "MapEditorUi.hpp"

#include "../map/MapEditor.hpp"
#include <imgui_stdlib.h>
#include <sstream>

#define _USE_MATH_DEFINES
#include <math.h>

#include "imgui-SFML.h"

MapEditorUi::MapEditorUi(MapEditor& map_editor) : mapEditor_(map_editor)
{
}

void MapEditorUi::render(Window& window)
{
	ImGui::ShowMetricsWindow(nullptr);
	tile_picker(window);

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

bool MapEditorUi::is_mouse_inside() const
{
	return is_mouse_inside_tilepicker();
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

void MapEditorUi::tileset_combo()
{
	std::stringstream ss;
	for (const auto& tset : mapEditor_.get_tilesets())
	{
		ss << tset.name_ << '\0';
	}

	ImGui::Combo("", &tilesetComboSelectedItemIndex_, ss.str().c_str());
}

void MapEditorUi::tileset_info() const
{
	if (tilesetComboSelectedItemIndex_ == -1)
		return;

	auto& tileset = mapEditor_.get_tilesets()[tilesetComboSelectedItemIndex_];
	ImGui::TextWrapped(tileset.desc_.c_str());
}

void MapEditorUi::tileset_sprites() const
{
	if (tilesetComboSelectedItemIndex_ == -1)
		return;

	auto& tileset = mapEditor_.get_tilesets()[tilesetComboSelectedItemIndex_];
	auto& sprites = tileset.get_sprites();

	ImGui::NewLine();

	const auto sprites_to_display_per_line = 3;
	auto sprites_on_current_line = 0;

	for (const auto& it : sprites)
	{
		const auto tex_size = sf::Vector2f(static_cast<float>(it.second.getTexture()->getSize().x), static_cast<float>(it.second.getTexture()->getSize().y));
		const auto tex_rect = sf::Vector2f(static_cast<float>(it.second.getTextureRect().left), static_cast<float>(it.second.getTextureRect().top));
		const auto spr_size = sf::Vector2f(static_cast<float>(it.second.getTextureRect().width), static_cast<float>(it.second.getTextureRect().height));

		const auto uv0 = get_uv0_coord(tex_size, tex_rect);
		const auto uv1 = get_uv1_coord(tex_size, tex_rect, spr_size);

		ImGui::SameLine();

		ImGui::PushID(it.first);
		if (ImGui::ImageButton(it.second, { 64, 64 }))
		{
			mapEditor_.set_selected_sprite(tileset, it.first);
		}
		ImGui::PopID();

		sprites_on_current_line++;

		if (sprites_on_current_line == sprites_to_display_per_line)
		{
			ImGui::NewLine();
			sprites_on_current_line = 0;
		}
	}
}

void MapEditorUi::selected_sprite() const
{
	// no need to draw the selected sprite if the mouse is inside any of the ui elements.
	if (is_mouse_inside())
		return;

	const auto selected_sprite = mapEditor_.get_selected_sprite();
	if (!selected_sprite)
		return;

	auto sprite = selected_sprite->get_sprite();

	auto sprite_rotation = selected_sprite->get_rotation();
	auto radians = (sprite_rotation / 180) * M_PI;

	const auto mouse = ImGui::GetMousePos();
	ImGui::SetNextWindowPos({mouse.x + 30, mouse.y});
	auto uvs = selected_sprite->get_uvs();


	if (ImGui::Begin("selectedSprite", nullptr, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar))
	{
		ImGui::ImageQuad(
			reinterpret_cast<void*>(sprite.getTexture()->getNativeHandle()),
			{ 64, 64 },
			radians,
			uvs[0],
			uvs[1],
			uvs[2],
			uvs[3]
		);
	}

	ImGui::End();

	//auto draw_list = ImGui::GetWindowDrawList();
	//auto size = ImVec2(64, 64);

	//const ImVec2 p = ImGui::GetCursorScreenPos();
	//ImGui::Dummy(size);

	//ImVec2 a(p.x, p.y); // top left
	//ImVec2 c(p.x + size.x, p.y + size.y); // bottom right
	//ImVec2 b(c.x, a.y); // top right
	//ImVec2 d(a.x, c.y); // bottom left

	//draw_list->PushTextureID(reinterpret_cast<void*>(sprite.getTexture()->getNativeHandle()));
	//draw_list->PrimReserve(6, 4);
	//draw_list->PrimQuadUV(a, b, c, d, uvs[0], uvs[1], uvs[2], uvs[3], IM_COL32_WHITE);
	//draw_list->PopTextureID();
}

void MapEditorUi::tile_picker(Window& window)
{
	tilePickerW_ = 256;
	tilePickerH_ = 640;

	tilepickerX_ = static_cast<float>(window.get().getSize().x - tilePickerW_);
	tilepickerY_ = 0;

	ImGui::SetNextWindowSize({ tilePickerW_, tilePickerH_ }); //4 tiles in width, 10 tiles in height
	ImGui::SetNextWindowPos({ tilepickerX_ , tilepickerY_ });

	tilepickerVisible_ = ImGui::Begin("Tilepicker", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
	if (tilepickerVisible_)
	{
		tileset_combo();
		tileset_sprites();
	}

	ImGui::End();
}

bool MapEditorUi::is_mouse_inside_tilepicker() const
{
	const auto mouse = ImGui::GetMousePos();

	const auto start_x = tilepickerX_;
	const auto start_y = tilepickerY_;

	const auto end_x = tilepickerX_ + tilePickerW_;
	const auto inside_x = mouse.x > start_x && mouse.x < end_x;

	if (!tilepickerVisible_)
	{
		//tilepicker collapsed but the titlebar is still there so check if the mouse is in it.
		const auto inside_tb_x = inside_x;
		const auto inside_tb_y = mouse.y > start_y && mouse.y < (start_y + 30);

		return inside_tb_x && inside_tb_y;
	}

	const auto end_y = tilepickerY_ + tilePickerH_;
	const auto inside_y = mouse.y > start_y && mouse.y < end_y;

	return inside_x && inside_y;
}

ImVec2 MapEditorUi::get_uv0_coord(const sf::Vector2f& tex_size, const sf::Vector2f& tex_rect)
{
	return ImVec2(tex_rect.x / tex_size.x, tex_rect.y / tex_size.y);
}

ImVec2 MapEditorUi::get_uv1_coord(const sf::Vector2f& tex_size, const sf::Vector2f& tex_rect, const sf::Vector2f spr_size)
{
	return ImVec2((tex_rect.x + spr_size.x) / tex_size.x, (tex_rect.y + spr_size.y) / tex_size.y);
}
