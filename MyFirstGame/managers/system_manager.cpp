#include "system_manager.hpp"

namespace mfg
{
	namespace managers
	{
		std::unique_ptr<input_system> system_manager::inputsys;
		static system_manager* instance;

		system_manager::system_manager()
		{
			instance = this;
		}

		system_manager * system_manager::getInstance()
		{
			return instance;
		}
	}
}