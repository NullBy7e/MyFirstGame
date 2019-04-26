#include "health.hpp"

namespace mfg {
	namespace components {
		HealthComponent::HealthComponent()
		{
		}

		HealthComponent::HealthComponent(float health)
		{
			this->health = health;
		}

		HealthComponent::~HealthComponent()
		{
		}

		float HealthComponent::getHealth()
		{
			return health;
		}
	}
}