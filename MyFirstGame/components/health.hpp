#pragma once

namespace mfg
{
	namespace components
	{
		class HealthComponent
		{
		public:
			         HealthComponent() = default;
			explicit HealthComponent(float health);

			float getHealth() const;
		private:
			float health_{};
		};
	}
}
