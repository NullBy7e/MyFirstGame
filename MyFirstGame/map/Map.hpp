#pragma once
#include <SFML/Graphics/Drawable.hpp>

class Map final : public sf::Drawable
{
public:
	static Map create();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

