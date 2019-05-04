#include <SFML/Graphics/RenderTarget.hpp>

#include "MapEditor.hpp"

MapEditor::MapEditor()
{
	map_ = Map::create();
}

MapEditor::MapEditor(const Map& map) : map_(map)
{
}

void MapEditor::draw(sf::RenderTarget& target, const sf::RenderStates states) const
{
	target.draw(grid_, states);

	if(map_.has_value())
		target.draw(map_.value(), states);
}
