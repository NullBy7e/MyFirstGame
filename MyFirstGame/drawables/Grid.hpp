#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/VertexArray.hpp>

class Grid final : public sf::Drawable
{
public:
	Grid(sf::Vector2u grid_size, sf::Vector2u tile_size);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	sf::VertexArray vertices_{ sf::Lines };
};

