#pragma once

#include "entt/entt.hpp"

#include "../components/enemy.hpp"
#include "../components/player.hpp"

namespace mfg {
	namespace registries {
		class entity_registry : public entt::registry
		{
		};
	}
}