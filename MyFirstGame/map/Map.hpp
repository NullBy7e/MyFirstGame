#pragma once
#include <SFML/Graphics/Drawable.hpp>
#include <xstring>
#include "Tile.hpp"

class Map final : public sf::Drawable
{
public:
	static Map create(const std::string& name);
	explicit Map(const std::string& name);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	std::string& get_name();
	std::string& get_desc();

	Tile* get_tile(const unsigned int column, const unsigned row);
	void add_tile(const unsigned int column, const unsigned int row, Sprite& sprite);
	void remove_tile(unsigned column, unsigned row);
	std::map<std::pair<unsigned int, unsigned int>, Tile>& get_tiles();

	sf::Vector2u& get_tile_size();
private:
	std::string name_;
	std::string desc_;

	sf::Vector2u pixelSize_{1280, 1024};
	sf::Vector2u tileSize_{64u,64u};

	/**
	 * \brief contains the tiles that are placed on the current map.
	 * the key is a std::pair that contains the column and row index.
	 */	
	std::map<std::pair<unsigned int, unsigned int>, Tile> tiles_;
};

