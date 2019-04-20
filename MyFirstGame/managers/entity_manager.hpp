#pragma once

#include "../registries//entity_registry.hpp"
#include "../components/components.hpp"

using namespace mfg::registries;
using namespace mfg::components;

namespace mfg
{
	namespace managers
	{
		class entity_manager
		{
		public:
			entity_manager();

			static entity_registry* getEntities();

			static mfg::components::player getPlayerEntity();

			static entt::entity getPlayer();

			static void setPlayer(unsigned int id);

			static entity_manager* getInstance();
		};
	}
}