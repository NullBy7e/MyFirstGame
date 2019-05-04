#pragma once
#include <SFML/Graphics/Drawable.hpp>
#include "../drawables/Grid.hpp"
#include "Map.hpp"
#include <optional>
#include "TileSet.hpp"

class MapEditor final : public sf::Drawable
{
public:
	explicit MapEditor(const Map& map);
	MapEditor();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
	Grid grid_{ {1280, 1024}, {16, 16} };
	std::optional<Map> map_;
	std::vector<TileSet> tilesets_;

	bool load_tilesets();
};

