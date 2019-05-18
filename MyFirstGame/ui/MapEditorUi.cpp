#include "MapEditorUi.hpp"

#include "../map/MapEditor.hpp"
#include <imgui_stdlib.h>
#include <sstream>

MapEditorUi::MapEditorUi(MapEditor& map_editor) : mapEditor_(map_editor)
{
}

void MapEditorUi::render()
{
	ImGui::Begin("Map Editor");

	if (ImGui::BeginTabBar("TabItems"))
	{
		if (ImGui::BeginTabItem("Properties", &propertiesTabEnabled_))
		{
			map_name_text_input();
			map_desc_text_input();

			ImGui::EndTabItem();
		}

		if (ImGui::BeginTabItem("Tilesets", &tilesetsTabEnabled_))
		{
			tileset_combo();
			tileset_info();
			tileset_sprites();

			ImGui::EndTabItem();
		}

		ImGui::EndTabBar();
	}

	ImGui::End();

	selected_sprite();
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

	ImGui::Combo("Tilesets", &tilesetComboSelectedItemIndex_, ss.str().c_str());
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

	const auto sprites_to_display_per_line = 10;
	auto sprites_on_current_line = 0;

	for(const auto& it : sprites)
	{
		const auto tex_size = sf::Vector2f(static_cast<float>(it.second.getTexture()->getSize().x), static_cast<float>(it.second.getTexture()->getSize().y));
		const auto tex_rect = sf::Vector2f(static_cast<float>(it.second.getTextureRect().left), static_cast<float>(it.second.getTextureRect().top));
		const auto spr_size = sf::Vector2f(static_cast<float>(it.second.getTextureRect().width), static_cast<float>(it.second.getTextureRect().height));
		
		const auto uv0 = get_uv0_coord(tex_size, tex_rect);
		const auto uv1 = get_uv1_coord(tex_size, tex_rect, spr_size);

		ImGui::SameLine();

		ImGui::PushID(it.first);
		if(ImGui::ImageButton(reinterpret_cast<void*>(it.second.getTexture()->getNativeHandle()), ImVec2(64, 64), 
			ImVec2(uv0),
			ImVec2((uv1))))
		{
			mapEditor_.set_selected_sprite(tileset, it.first);
		}
		ImGui::PopID();

		sprites_on_current_line++;

		if(sprites_on_current_line == sprites_to_display_per_line)
		{
			ImGui::NewLine();
			sprites_on_current_line = 0;
		}
	}
}

void MapEditorUi::selected_sprite() const
{
	const auto selected_sprite = mapEditor_.get_selected_sprite();
	if (selected_sprite == nullptr)
		return;

	auto sprite = selected_sprite->get_sprite();

	const auto mouse = ImGui::GetMousePos();
	ImGui::SetNextWindowPos({ mouse.x + 20, mouse.y + 10 });
	if (ImGui::Begin("selectedSprite", nullptr, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize))
	{
		ImGui::Image(reinterpret_cast<void*>(sprite.getTexture()->getNativeHandle()), ImVec2(64, 64),
			ImVec2(selected_sprite->get_uv0_coord()),
			ImVec2((selected_sprite->get_uv1_coord())));
	}

	ImGui::End();
}

ImVec2 MapEditorUi::get_uv0_coord(const sf::Vector2f& tex_size, const sf::Vector2f& tex_rect)
{
	return ImVec2(tex_rect.x / tex_size.x, tex_rect.y / tex_size.y);
}

ImVec2 MapEditorUi::get_uv1_coord(const sf::Vector2f& tex_size, const sf::Vector2f& tex_rect, const sf::Vector2f spr_size)
{
	return ImVec2((tex_rect.x + spr_size.x) / tex_size.x, (tex_rect.y + spr_size.y) / tex_size.y);
}
