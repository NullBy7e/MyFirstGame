#pragma once

#include <string>

namespace mfg
{
	namespace components
	{
		class ActorComponent
		{
		public:
			explicit ActorComponent(std::string name);
			         ActorComponent() = default;

			std::string getName() const;
		private:
			std::string name_;
		};
	}
}
