#pragma once

#include "components/actor.hpp"
#include "components/animation.hpp"
#include "components/health.hpp"
#include "components/position.hpp"
#include "components/sprite.hpp"

using namespace mfg::components;

namespace mfg
{
	namespace core
	{
		using PlayerData = std::tuple<ActorComponent, HealthComponent, AnimationComponent, SpriteComponent, PositionComponent>;
	}
}