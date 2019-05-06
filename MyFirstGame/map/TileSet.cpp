#include "TileSet.hpp"
#include <SFML/System/Vector2.hpp>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <functional>
#include <imgui.h>

TileSet::TileSet(const std::string& name, const std::string& path, const sf::Vector2i tilesize)
{
	std::cout << "Loading tileset " << "\"" << name << "\"" << ":" << "\"" << path << "\"" << std::endl;

	if(!texture_.loadFromFile(path))
	{
		std::cerr << "The tileset failed to load due to missing assets, please reinstall the game." << std::endl;
		return;
	}

	// read the meta file
	const auto meta_file_path = std::filesystem::path(path).parent_path().generic_string() + "/" + std::filesystem::
		path(path).filename().replace_extension("meta").generic_string();

	if (!load_meta_file(meta_file_path))
	{
		std::cerr << "The tileset failed to load due to missing assets, please reinstall the game." << std::endl;
		return;
	}

	// slice up the image into multiple sf::Texture
	const int cols = texture_.getSize().x / tilesize.x;
	const int rows = texture_.getSize().y / tilesize.y;

	// each col + row combination contains a sprite
	for (auto col = 0; col < cols; ++col)
	{
		for (auto row = 0; row < rows; ++row)
		{
			// the xy location of the sprite in the image
			const auto x_pos = col * tilesize.x;
			const auto y_pos = row * tilesize.y;

			const auto sprite_index = sprites_.empty() ? 1 : sprites_.size() + 1;
			sprites_[sprite_index] = sf::Sprite(texture_, { x_pos, y_pos, tilesize.x, tilesize.y });;
		}
	}
}

std::map<int, sf::Sprite>& TileSet::get_sprites()
{
	return sprites_;
}

bool TileSet::load_meta_file(const std::string& meta_file_path)
{
	std::cout << "Loading meta file: " << meta_file_path << std::endl;

	if (!std::filesystem::exists(meta_file_path))
		return false;

	std::ifstream meta_file(meta_file_path);
	if (meta_file.fail())
	{
		meta_file.close();
		return false;
	}

	std::string line;
	while (std::getline(meta_file, line))
	{
		if (line.empty())
			continue;

		//key and value
		auto str_split = split(line, ':');
		auto key = str_split[0];
		auto val = str_split[1];

		if (key == "tileset_name")
		{
			name_ = val;
		}

		if (key == "tileset_desc")
		{
			desc_ = val;
		}

		if (key == "tileset_stid")
		{
			stid_ = std::stoi(val);
		}

		if (key == "tileset_size")
		{
			auto size_split = split(val, 'x');
			size_ = sf::Vector2i(std::stoi(size_split[0]), std::stoi(size_split[1]));
		}
	}
	meta_file.close();

	return true;
}

std::vector<std::string> TileSet::split(std::string& str_to_split, const char delimiter) const
{
	std::stringstream ss(str_to_split);
	std::string item;
	std::vector<std::string> result;
	while (std::getline(ss, item, delimiter))
	{
		item.erase(std::remove_if(item.begin(), item.end(),
		                          [](const char c)
		                          {
			                          return !(std::isspace(c, {}) || std::isalnum(c, {}) || c == '_');
		                          }),
		           item.end());

		result.push_back(item);
	}
	return result;
}
