#pragma once

namespace mfg {
	namespace components {
		class HealthComponent
		{
		public:
			HealthComponent();
			HealthComponent(float health);
			~HealthComponent();

			float getHealth();
		private:
			float health;
		};
	}
}