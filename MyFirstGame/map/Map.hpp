#pragma once
#include <SFML/Graphics/Drawable.hpp>
#include <xstring>

class Map final : public sf::Drawable
{
public:
	static Map create(const std::string& name);
	explicit Map(const std::string& name);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	std::string& get_name();
	std::string& get_desc();

private:
	std::string name_;
	std::string desc_;
};

