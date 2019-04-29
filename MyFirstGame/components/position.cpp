#include "position.hpp"

namespace mfg
{
	namespace components
	{
		PositionComponent::PositionComponent(const float x, const float y) : x_(x), y_(y)
		{
		}

		void PositionComponent::setPosition(const float x, const float y)
		{
			this->x_ = x;
			this->y_ = y;
		}

		sf::Vector2f PositionComponent::getPosition() const
		{
			return sf::Vector2f(x_, y_);
		}

		sf::Vector2f PositionComponent::getPosition(const float height_offset) const
		{
			return sf::Vector2f(x_, y_ - height_offset);
		}
	}
}
