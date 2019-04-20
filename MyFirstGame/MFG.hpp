#pragma once

#include "entt/entt.hpp"

#include "managers/system_manager.hpp"
#include "managers/entity_manager.hpp"

using namespace mfg::managers;

namespace mfg
{
	class MFG
	{
	public:
		static system_manager* getSystemManager() {
			if (!sysmgr)
			{
				sysmgr.reset(new system_manager);
			}

			return sysmgr.get();
		}

		static entity_manager* getEntityManager() {
			if (!entmgr)
			{
				entmgr.reset(new entity_manager);
			}

			return entmgr.get();
		}

	private:
		static std::unique_ptr<system_manager> sysmgr;
		static std::unique_ptr<entity_manager> entmgr;
	};
}