#include "MFG.hpp"

namespace mfg
{
	std::unique_ptr<system_manager> MFG::sysmgr;
	std::unique_ptr<entity_manager> MFG::entmgr;
	std::unique_ptr<texture_manager> MFG::texmgr;
	std::unique_ptr<map_manager> MFG::mapmgr;

	void MFG::init()
	{
		sysmgr.reset(new system_manager);
		entmgr.reset(new entity_manager);
		texmgr.reset(new texture_manager);
		mapmgr.reset(new map_manager);
	}

	system_manager* MFG::getSystemManager()
	{
		return sysmgr.get();
	}

	entity_manager* MFG::getEntityManager()
	{
		return entmgr.get();
	}

	texture_manager* MFG::getTextureManager()
	{
		return texmgr.get();
	}

	map_manager* MFG::getMapManager()
	{
		return mapmgr.get();
	}
}