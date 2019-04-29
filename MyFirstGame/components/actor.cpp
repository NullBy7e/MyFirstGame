#include "actor.hpp"
#include <utility>

namespace mfg
{
	namespace components
	{
		ActorComponent::ActorComponent(std::string name) : name_(std::move(name))
		{
		}

		std::string ActorComponent::getName() const
		{
			return name_;
		}
	}
}
