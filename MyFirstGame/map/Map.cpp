#include <SFML/Graphics/RenderTarget.hpp>
#include "Map.hpp"

Map Map::create(const std::string& name)
{
	return Map(name);
}

Map::Map(const std::string& name) : name_(name)
{
}

void Map::draw(sf::RenderTarget& target, const sf::RenderStates states) const
{
	for(auto& tile : tiles_)
	{
		tile.second.draw(target, states);
	}
}

std::string& Map::get_name()
{
	return name_;
}

std::string& Map::get_desc()
{
	return desc_;
}

Tile* Map::get_tile(const unsigned column, const unsigned row)
{
	const auto pair = std::make_pair(column, row);

	if (tiles_.find(pair) == tiles_.end())
	{
		//no matching pair found
		return nullptr;
	}

	return std::addressof(tiles_.at(pair));
}

void Map::add_tile(const unsigned int column, const unsigned int row, Sprite& sprite)
{	
	const auto pair = std::make_pair(column, row);

	if (tiles_.find(pair) != tiles_.end())
	{
		//delete found tile
		tiles_.erase(pair);
	}

	//adds a new tile with the matching pair
	tiles_.emplace(pair, Tile(column, row, get_tile_size(), sprite));
}

void Map::remove_tile(const unsigned int column, const unsigned int row)
{
	const auto pair = std::make_pair(column, row);

	if (tiles_.find(pair) != tiles_.end())
	{
		//delete found tile
		tiles_.erase(pair);
	}
}

std::map<std::pair<unsigned int, unsigned int>, Tile>& Map::get_tiles()
{
	return tiles_;
}

sf::Vector2u& Map::get_tile_size()
{
	return tileSize_;
}
