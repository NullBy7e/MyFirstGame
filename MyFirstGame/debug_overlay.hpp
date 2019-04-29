#pragma once

#include <SFML/Graphics.hpp>

#include "window.hpp"

#include "managers/entity_manager.hpp"

using namespace mfg::managers;

namespace mfg
{
	namespace core
	{
		class DebugOverlay final : public sf::Transformable, public sf::Drawable
		{
		public:
			DebugOverlay(Window& window, EntityManager& entmgr);

			void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		private:
			Window&        window_;
			EntityManager& entmgr_;

			sf::Font font_;
		};
	}
}
