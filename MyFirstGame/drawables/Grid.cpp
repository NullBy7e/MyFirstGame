#include "Grid.hpp"
#include <SFML/Graphics/RenderTarget.hpp>

Grid::Grid(const sf::Vector2u grid_size, const sf::Vector2u tile_size)
{
	for (auto col = 0u; col < grid_size.x / tile_size.x; ++col)
	{
		const auto x_pos = static_cast<float>(col * tile_size.x);

		for (auto row = 0u; row < grid_size.y / tile_size.y; ++row)
		{
			const auto y_pos = static_cast<float>(row * tile_size.y);

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
