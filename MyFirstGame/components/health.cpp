#include "health.hpp"

namespace mfg
{
	namespace components
	{
		HealthComponent::HealthComponent(const float health) : health_(health)
		{
		}

		float HealthComponent::getHealth() const
		{
			return health_;
		}
	}
}
