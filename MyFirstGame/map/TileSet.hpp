#pragma once

#include <string>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <map>
#include <SFML/Graphics/Sprite.hpp>

class TileSet
{
public:
	TileSet(const std::string& name, const std::string& path, sf::Vector2u tilesize);

	std::map<int, sf::Sprite>& get_sprites();
	sf::Sprite get_sprite(const int sprite_index);

	std::string name_;
	std::string desc_;
	int stid_{};
	sf::Vector2u size_;

private:
	sf::Texture texture_;
	std::map<int, sf::Sprite> sprites_;

	bool load_meta_file(const std::string& meta_file_path);
	std::vector<std::string> split(std::string& str_to_split, char delimiter) const;
};
