#include "map_renderer.hpp"

namespace mfg
{
	namespace core
	{
		MapRenderer::MapRenderer(Window& window) : window(window)
		{
			DEBUG_MSG("CTOR " << "	 [" << std::addressof(*this) << "]	MapRenderer");
		}

		MapRenderer::~MapRenderer()
		{
			DEBUG_MSG("DTOR " << "	 [" << std::addressof(*this) << "]	MapRenderer");
		}

		void MapRenderer::render(Viewport& viewport, Map& map)
		{
			drawTiles(viewport, map);
			drawEntities(map);
		}

		void MapRenderer::drawTiles(Viewport& viewport, Map& map)
		{
			/* get XY->tile_id mapping for the current viewport */
			for (auto mapping : map.getMappings
			(
				viewport.getViewport().left,
				viewport.getViewport().top,

				viewport.getViewport().top + viewport.getDimensions().y,
				viewport.getViewport().left + viewport.getDimensions().x
			))
			{
				auto pair = mapping.first;
				auto x = pair.first;
				auto y = pair.second;
				auto tiles = mapping.second;

				for (auto tile_id : tiles)
				{
					if (tile_id == 0)
						continue;

					auto sprite = map.getSpriteByTileId(tile_id);
					sprite.setPosition({ x, y });

					window.draw(sprite);
				}
			}
		}

		void MapRenderer::drawEntities(Map& map)
		{
			const auto view = map.getEntities();

			for (auto entity : view)
			{
				auto& position = view.get<PositionComponent>(entity);
				auto& sprite = view.get<SpriteComponent>(entity);

				sprite.update(position.getPosition());
				window.draw(sprite);
			}
		}
	}
}