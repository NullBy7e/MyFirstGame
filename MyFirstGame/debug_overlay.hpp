#pragma once

#include <sstream>
#include <string>

#include <SFML/Graphics.hpp>

#include "macros.hpp"
#include "window.hpp"

#include "managers/entity_manager.hpp"

using namespace mfg::managers;

namespace mfg
{
	namespace core
	{
		class DebugOverlay : public sf::Transformable, public sf::Drawable
		{
		public:
			DebugOverlay(EntityManager& entmgr, Window& window);
			~DebugOverlay();

			void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		private:
			Window& window;
			EntityManager& entmgr;

			sf::Font font;
		};
	}
}