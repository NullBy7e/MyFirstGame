#include "map_renderer.hpp"

namespace mfg
{
	namespace core
	{
		MapRenderer::MapRenderer(Window& window) : window_(window)
		{
		}

		void MapRenderer::render(Viewport& viewport, Map& map) const
		{
			drawTiles(viewport, map);
			drawEntities(map);
		}

		void MapRenderer::drawTiles(Viewport& viewport, Map& map) const
		{
			/* get XY->tile_id mapping for the current viewport */
			for (auto& [pair, tiles] : map.getMappings
			     (
				     viewport.getViewport().left,
				     viewport.getViewport().top,

				     viewport.getViewport().top + viewport.getDimensions().y,
				     viewport.getViewport().left + viewport.getDimensions().x
			     ))
			{
				const auto x = pair.first;
				const auto y = pair.second;

				for (auto tile_id : tiles)
				{
					if (tile_id == 0)
						continue;

					auto sprite = map.getSpriteByTileId(tile_id);
					sprite.setPosition({x, y});

					window_.draw(sprite);
				}
			}
		}

		void MapRenderer::drawEntities(Map& map) const
		{
			const auto view = map.getEntities();

			for (auto entity : view)
			{
				auto& position = view.get<PositionComponent>(entity);
				auto& sprite   = view.get<SpriteComponent>(entity);

				sprite.update(position.getPosition());
				window_.draw(sprite);
			}
		}
	}
}
