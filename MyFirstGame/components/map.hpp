#pragma once

#include <SFML/Graphics.hpp>

namespace mfg {
	namespace components {
		struct map
		{
			map(int id) : id(id)
			{
			}

			int id;
		};
	}
}