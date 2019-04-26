#include "map_renderer.hpp"

namespace mfg
{
	namespace core
	{
		MapRenderer::MapRenderer()
		{
			DEBUG_MSG("CTOR " << "	 [" << std::addressof(*this) << "]	MapRenderer");
		}

		MapRenderer::~MapRenderer()
		{
			DEBUG_MSG("DTOR " << "	 [" << std::addressof(*this) << "]	MapRenderer");
		}

		std::vector<sf::Sprite> MapRenderer::getSprites(Viewport* viewport, Map* map)
		{
			auto sprites = drawTiles(viewport, map);
			auto entities = drawEntities(map);

			sprites.insert(sprites.end(), entities.begin(), entities.end());
			return sprites;
		}

		std::vector<sf::Sprite> MapRenderer::drawTiles(Viewport* viewport, Map* map)
		{
			std::vector<sf::Sprite> sprites;

			/* draw every tile that's inside the viewport */
			for (auto layer : map->tile_layers)
			{
				for (int col = ((viewport->getCenter().x / map->tile_width) - viewport->getTileWidth()); col < map->width; ++col)
				{
					if (col < 0) //nothing to draw?
						continue;

					for (int row = ((viewport->getCenter().y / map->tile_height) - viewport->getTileHeight()); row < map->height; ++row)
					{
						if (row < 0) //nothing to draw?
							continue;

						/* the tile number to draw */
						auto tile = layer.tiles[(row * map->width) + col];

						/* tile number 0 means that we don't need to draw this col+rol */
						if (tile.id == 0)
							continue;

						/* get the sprite that belongs to the tile number */
						auto sprite = map->sprites[tile.id];

						/* set the sprite's position */
						sprite.setPosition(sf::Vector2f(col * map->tile_width, row * map->tile_height));

						sprites.push_back(sprite);
					}
				}
			}

			return sprites;
		}

		std::vector<sf::Sprite> MapRenderer::drawEntities(Map* map)
		{
			std::vector<sf::Sprite> sprites;

			auto view = map->getEntities();

			for (auto entity : view)
			{
				auto& position = view.get<PositionComponent>(entity);
				auto& sprite = view.get<SpriteComponent>(entity);

				sprite.update(position.getPosition());
				sprites.push_back(sprite);
			}

			return sprites;
		}
	}
}