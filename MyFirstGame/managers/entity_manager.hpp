#pragma once

#include "../registries//entity_registry.hpp"

using namespace mfg::registries;

namespace mfg
{
	namespace managers
	{
		class entity_manager
		{
		public:
			static entity_registry* getEntities() {
				if (!entities)
				{
					entities.reset(new entity_registry);
				}

				return entities.get();
			}
		private:
			static std::unique_ptr<entity_registry> entities;
		};
	}
}