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
	
}

std::string& Map::get_name()
{
	return name_;
}

std::string& Map::get_desc()
{
	return desc_;
}
