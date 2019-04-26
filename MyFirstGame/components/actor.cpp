#include "actor.hpp"

namespace mfg
{
	namespace components
	{
		ActorComponent::ActorComponent(std::string name) : name(name)
		{
		}

		ActorComponent::ActorComponent()
		{
		}

		ActorComponent::~ActorComponent()
		{
		}

		std::string ActorComponent::getName()
		{
			return name;
		}
	}
}