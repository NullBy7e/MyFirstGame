#include "Tilepicker.hpp"
#include <imgui.h>
#include <iosfwd>
#include <sstream>
#include "../../map/MapEditor.hpp"
#include "imgui-SFML.h"

Tilepicker::Tilepicker(std::vector<TileSet>* tilesets, const float width, const float height, const float x, const float y)
	:
	UiElement(width, height, x, y),
	tilesets_(tilesets)
{
}

void Tilepicker::draw()
{
	ImGui::SetNextWindowSize({ width_, height_ });
	ImGui::SetNextWindowPos({ x_, y_ });

	isVisible_ = ImGui::Begin("Tilepicker", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
	if (isVisible_)
	{
		tileset_combo();
		tileset_sprites();
	}

	ImGui::End();
}

void Tilepicker::tileset_combo()
{
	std::stringstream ss;
	for (const auto& tset : *tilesets_)
	{
		ss << tset.name_ << '\0';
	}

	ImGui::Combo("", &tilesetComboSelectedItemIndex_, ss.str().c_str());
}

void Tilepicker::tileset_sprites()
{
	if (tilesetComboSelectedItemIndex_ == -1)
		return;

	auto& tileset = (*tilesets_)[tilesetComboSelectedItemIndex_];
	auto& sprites = tileset.get_sprites();

	ImGui::NewLine();

	const auto sprites_to_display_per_line = 3;
	auto sprites_on_current_line = 0;

	for (const auto& it : sprites)
	{
		ImGui::SameLine();

		ImGui::PushID(it.first);
		if (ImGui::ImageButton(it.second, { 64, 64 }))
		{
			cb_->cb_tilepicker_sprite_selected(tileset, it.first);
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