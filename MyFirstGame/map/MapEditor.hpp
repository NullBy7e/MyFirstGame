#pragma once

#include "../drawables/Grid.hpp"
#include "Map.hpp"
#include <optional>
#include "TileSet.hpp"
#include "../ui/MapEditorUI.hpp"
#include "Sprite.hpp"

class Window;

class MapEditor
{
public:
	explicit MapEditor(const Map& map);
	MapEditor();

	void render(Window& window);
	
	std::vector<TileSet>& get_tilesets();
	std::string& get_map_name();
	std::string& get_map_desc();

	void set_selected_sprite(TileSet& tile_set, const int sprite_index);
	Sprite& get_selected_sprite() const;
private:
	Grid grid_{ {1280, 1024}, {64, 64} };
	std::vector<TileSet> tilesets_;

	std::optional<Map> map_;
	std::shared_ptr<Sprite> selectedSprite_;

	bool load_tilesets();

	MapEditorUi ui_{*this};
};

