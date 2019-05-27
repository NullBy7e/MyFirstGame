#include <filesystem>

#include "MapEditor.hpp"
#include <iostream>
#include "../core/Window.hpp"

MapEditor::MapEditor()
{
	map_ = Map::create("New map");

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
		return false;

	auto tileset_count = 0;
	for (const auto& file : std::filesystem::directory_iterator(path))
	{
		if (file.path().filename().extension() != ".png")
			continue;

		tileset_count++;
	}

	// reserve space in the vector so that internal references are not invalidated on emplace_back due to internal copy/move operations
	tilesets_.reserve(tileset_count);

	for (const auto& file : std::filesystem::directory_iterator(path))
	{
		if (file.path().filename().extension() != ".png")
			continue;

		auto file_name_no_ext = file.path().filename().replace_extension().generic_string();
		auto file_path = file.path().generic_string();

		tilesets_.emplace_back(file_name_no_ext, file_path, sf::Vector2u(16, 16));
	}

	return true;
}

void MapEditor::render(Window& window)
{
	if (grid_.has_value())
	{
		window.draw(grid_.value());
	}
	else 
	{
		grid_ = Grid{ window.get().getSize(), map_->get_tile_size() };
	}

	if (map_.has_value())
		window.draw(map_.value());

	ui_.render();
}

void MapEditor::process_event(const sf::Event& event)
{
	switch(event.type)
	{
	case sf::Event::MouseButtonPressed:
		mouseButtonPressed_ = true;
		mouseButton_ = event.mouseButton.button;

		if (event.mouseButton.button == sf::Mouse::Left)
		{
			add_selected_sprite_to_tile({ event.mouseButton.x, event.mouseButton.y });
		}

		if (event.mouseButton.button == sf::Mouse::Right)
		{
			if(selectedSprite_ == nullptr)
			{
				clear_clicked_tile({ event.mouseButton.x, event.mouseButton.y });
			}
			else
			{
				clear_selected_sprite();
			}		
		}
		break;
	case sf::Event::MouseButtonReleased:
		mouseButtonPressed_ = false;
		break;
	default: break;
	}
}

std::vector<TileSet>& MapEditor::get_tilesets()
{
	return tilesets_;
}

std::string& MapEditor::get_map_name()
{
	return map_.value().get_name();
}

std::string& MapEditor::get_map_desc()
{
	return map_.value().get_desc();
}

void MapEditor::set_selected_sprite(TileSet& tile_set, const int sprite_index)
{
	clear_selected_sprite();
	selectedSprite_ = std::make_shared<Sprite>(tile_set, sprite_index);
}

std::shared_ptr<Sprite>& MapEditor::get_selected_sprite()
{
	return selectedSprite_;
}

std::pair<unsigned, unsigned> MapEditor::get_column_row_at_mouse_pos(sf::Vector2i mouse_pos)
{
	return {(mouse_pos.x / map_->get_tile_size().x), mouse_pos.y / map_->get_tile_size().y};
}

void MapEditor::add_selected_sprite_to_tile(const sf::Vector2i mouse_pos)
{
	const auto selected_sprite = get_selected_sprite();
	if (selected_sprite == nullptr)
		return;

	const auto pair = get_column_row_at_mouse_pos(mouse_pos);
	map_->add_tile(pair.first, pair.second, *selected_sprite);
}

void MapEditor::clear_clicked_tile(const sf::Vector2i mouse_pos)
{
	const auto pair = get_column_row_at_mouse_pos(mouse_pos);
	map_->remove_tile(pair.first, pair.second);
}

void MapEditor::clear_selected_sprite()
{
	selectedSprite_.reset();
}
