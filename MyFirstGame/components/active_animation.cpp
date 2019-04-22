#include "active_animation.hpp"

namespace mfg {
	namespace components {
		active_animation::active_animation(entity_animation& animation) : animation(std::addressof(animation))
		{
			name = animation.getName();
		}
	}
}