#pragma once

#include "entt/entt.hpp"

#include "managers/system_manager.hpp"
#include "managers/entity_manager.hpp"
#include "managers/texture_manager.hpp"
#include "managers/map_manager.hpp"

using namespace mfg::managers;

namespace mfg
{
	class MFG
	{
	public:
		static void init();

		static system_manager* getSystemManager();

		static entity_manager* getEntityManager();

		static texture_manager* getTextureManager();

		static map_manager* getMapManager();

	private:
		static std::unique_ptr<system_manager> sysmgr;
		static std::unique_ptr<entity_manager> entmgr;
		static std::unique_ptr<texture_manager> texmgr;
		static std::unique_ptr<map_manager> mapmgr;
	};
}