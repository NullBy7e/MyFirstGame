#pragma once

#include <memory>
#include "../systems/input_system.hpp"

using namespace mfg::systems;

namespace mfg
{
	namespace managers
	{
		class system_manager
		{
		public:
			static input_system* getInputSystem() {
				if (!inputsys)
				{
					inputsys.reset(new input_system);
				}

				return inputsys.get();
			}

		private:
			static std::unique_ptr<input_system> inputsys;
		};
	}
}