#include "debug_overlay.hpp"

namespace mfg
{
	namespace core
	{
		DebugOverlay::DebugOverlay(EntityManager& entmgr, Window& window) : entmgr(entmgr), window(window)
		{
			font.loadFromFile("fonts/arial.ttf");
		}

		DebugOverlay::~DebugOverlay()
		{
		}

		void DebugOverlay::draw(sf::RenderTarget & target, sf::RenderStates states) const
		{
			sf::Vector2f mouse_position = window.mapPixelToCoords(sf::Mouse::getPosition(window));

			auto view = target.getView();
			auto viewport = view.getViewport();

			if (mouse_position.x >= viewport.left && mouse_position.x <= (viewport.left + view.getSize().x))
			{
				/* mouse is inside the current window */
				if (mouse_position.y >= viewport.top && mouse_position.y <= (viewport.top + view.getSize().y))
				{
					/* rectangle drawn next to mouse with current position relative to window */
					sf::RectangleShape position_shape({ 85, 60 });

					auto position_shape_offset_x = 30;
					auto position_shape_offset_y = 30;

					auto position_shape_x = mouse_position.x + position_shape_offset_x;
					auto position_shape_y = mouse_position.y + position_shape_offset_y;

					/* if the shape is going to be drawn off window/screen... */
					if ((position_shape_x + position_shape.getSize().x) >= view.getSize().x)
					{
						position_shape_x = mouse_position.x - (position_shape.getSize().x + position_shape_offset_x);
					}
					else if ((position_shape_y + position_shape.getSize().y) >= view.getSize().y)
					{
						position_shape_y = mouse_position.y - (position_shape.getSize().y - position_shape_offset_y);
					}

					position_shape.setPosition(position_shape_x, position_shape_y);

					/* X text */
					std::stringstream ss_x;
					ss_x << "X " << mouse_position.x;
					sf::Text position_x_text(ss_x.str(), font, 18);
					position_x_text.setFillColor(sf::Color::Black);
					position_x_text.setPosition(position_shape.getPosition().x + 5, position_shape.getPosition().y + 5);

					/* Y text */
					std::stringstream ss_y;
					ss_y << "Y " << mouse_position.y;
					sf::Text position_y_text(ss_y.str(), font, 18);
					position_y_text.setFillColor(sf::Color::Black);
					position_y_text.setPosition(position_x_text.getPosition().x, position_x_text.getPosition().y + 28);

					/* entity information */
					auto group = entmgr.getEntities().group<PositionComponent, SpriteComponent, ActorComponent>();

					/* interate over a group that returns the position, sprite and actor components */
					group.each([this, mouse_position, position_shape_x, position_shape_y](auto entity, PositionComponent &position, SpriteComponent &sprite, ActorComponent &actor)
					{
						if (mouse_position.x > position.getPosition().x && mouse_position.x <= (position.getPosition().x + sprite.getLocalBounds().width))
						{
							if (mouse_position.y >= (position.getPosition().y - sprite.getLocalBounds().height) && mouse_position.y <= position.getPosition().y)
							{
								/* entity shape */
								std::stringstream ss_entity_name;
								ss_entity_name << "" << actor.getName();
								sf::Text entity_name_text(ss_entity_name.str(), font, 18);
								entity_name_text.setStyle(sf::Text::Style::Bold);
								entity_name_text.setFillColor(sf::Color::Black);

								sf::RectangleShape entity_shape({ entity_name_text.getLocalBounds().width + 20, 38 });

								auto entity_shape_x = position_shape_x;
								auto entity_shape_y = (position_shape_y - 10) - entity_shape.getLocalBounds().height;

								entity_shape.setPosition(entity_shape_x, entity_shape_y);
								entity_name_text.setPosition(entity_shape.getPosition().x + 10, entity_shape.getPosition().y + 10);

								this->window.draw(entity_shape);
								this->window.draw(entity_name_text);
							}
						}
					});

					window.draw(position_shape);
					window.draw(position_x_text);
					window.draw(position_y_text);
				}
			}
		}
	}
}