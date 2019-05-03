#include "Grid.hpp"
#include <SFML/Graphics/RenderTarget.hpp>

Grid::Grid(const sf::Vector2f grid_size, const sf::Vector2f tile_size)
{
	for (auto col = 0; col < grid_size.x / tile_size.x; ++col)
	{
		const auto x_pos = col * tile_size.x;

		for (auto row = 0; row < grid_size.y / tile_size.y; ++row)
		{
			const auto y_pos = row * tile_size.y;

			vertices_.append(sf::Vertex({ x_pos, y_pos }, sf::Color::White));
			vertices_.append(sf::Vertex({ x_pos + tile_size.x, y_pos }, sf::Color::White));
			vertices_.append(sf::Vertex({ x_pos + tile_size.x, y_pos }, sf::Color::White));
			vertices_.append(sf::Vertex({ x_pos + tile_size.x, y_pos + tile_size.y }, sf::Color::White));
			vertices_.append(sf::Vertex({ x_pos + tile_size.x, y_pos + tile_size.y }, sf::Color::White));
			vertices_.append(sf::Vertex({ x_pos, y_pos + tile_size.y }, sf::Color::White));
			vertices_.append(sf::Vertex({ x_pos, y_pos + tile_size.y }, sf::Color::White));
			vertices_.append(sf::Vertex({ x_pos, y_pos }, sf::Color::White));
		}
	}
}

void Grid::draw(sf::RenderTarget& target, const sf::RenderStates states) const
{
	target.draw(vertices_, states);
}
