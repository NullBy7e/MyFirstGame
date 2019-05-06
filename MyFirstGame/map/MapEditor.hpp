#pragma once
#include <SFML/Graphics/Drawable.hpp>
#include "../drawables/Grid.hpp"
#include "Map.hpp"
#include <optional>
#include "TileSet.hpp"
#include "../ui/MapEditorUI.hpp"

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
private:
	Grid grid_{ {1280, 1024}, {16, 16} };
	std::optional<Map> map_;
	std::vector<TileSet> tilesets_;

	bool load_tilesets();

	MapEditorUi ui_{*this};
};

