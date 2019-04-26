#include "position.hpp"

namespace mfg {
	namespace components {
		PositionComponent::PositionComponent()
		{
		}

		PositionComponent::PositionComponent(float x, float y) : x(x), y(y)
		{
		}

		PositionComponent::~PositionComponent()
		{
		}

		void PositionComponent::setPosition(float x, float y)
		{
			this->x = x;
			this->y = y;
		}

		sf::Vector2f PositionComponent::getPosition()
		{
			return sf::Vector2f(x, y);
		}

		sf::Vector2f PositionComponent::getPosition(float height_offset)
		{
			return sf::Vector2f(x, y - height_offset);
		}
	}
}