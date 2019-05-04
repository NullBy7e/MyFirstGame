#include <filesystem>

#include <SFML/Graphics/RenderTarget.hpp>
#include <imgui.h>

#include "MapEditor.hpp"
#include <iostream>

MapEditor::MapEditor()
{
	map_ = Map::create();

	if (!load_tilesets())
	{
		std::cerr << "The map failed to load due to missing assets, please reinstall the game." << std::endl;
		return;
	}


}

MapEditor::MapEditor(const Map& map) : map_(map)
{
}

bool MapEditor::load_tilesets()
{
	const std::string dir_assets = "assets";
	const std::string dir_tilesets = "tilesets";

	const auto path = dir_assets + "/" + dir_tilesets;

	if (!std::filesystem::exists(path))
		std::cerr << "The map failed to load due to missing assets, please reinstall the game." << std::endl;
	
	for (const auto& file : std::filesystem::directory_iterator(path))
	{
		if (file.path().filename().extension() != ".png")
			continue;

		auto file_name_no_ext = file.path().filename().replace_extension().generic_string();
		auto file_path = file.path().generic_string();

		tilesets_.emplace_back(file_name_no_ext, file_path, sf::Vector2i(16, 16));
	}

	return true;
}

void MapEditor::draw(sf::RenderTarget& target, const sf::RenderStates states) const
{
	target.draw(grid_, states);

	if (map_.has_value())
		target.draw(map_.value(), states);

	ImGui::Begin("Sample window");
	ImGui::End();
}
