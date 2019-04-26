#pragma once

#include <string>

namespace mfg
{
	namespace components
	{
		class ActorComponent
		{
		public:
			ActorComponent(std::string name);
			ActorComponent();
			~ActorComponent();

			std::string getName();
		private:
			std::string name;
		};
	}
}