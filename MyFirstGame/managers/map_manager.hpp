#pragma once

#include "../tmx//tmx_map.hpp"

#include "texture_manager.hpp"
#include "entity_manager.hpp"

#include "../components/components.hpp"

using namespace mfg::components;

namespace mfg {
	namespace managers {
		class map_manager
		{
		public:
			map_manager();

			TmxMap* loadMap(int id);

			int addMap(TmxMap map);

			TmxMap* getMap(int id);

			TmxMap* getCurrentMap();

			static map_manager* getInstance();
		private:
			std::vector<std::unique_ptr<TmxMap>> maps;
			std::unique_ptr<TmxMap> currentMap;
		};
	}
}