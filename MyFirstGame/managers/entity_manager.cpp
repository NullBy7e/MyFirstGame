#include "entity_manager.hpp"

namespace mfg
{
	namespace managers
	{
		static std::unique_ptr<entity_registry> entities;
		static entt::entity player_id;
		static entity_manager* instance;

		entity_manager::entity_manager()
		{
			instance = this;
		}

		entity_registry* entity_manager::getEntities()
		{
			if (!entities)
			{
				entities.reset(new entity_registry);
			}

			return entities.get();
		}

		template <class T>
		T getPlayerComponent()
		{
			entities.get<T>(this->getPlayer());
		}

		mfg::components::player entity_manager::getPlayerEntity()
		{
			auto entities = getEntities();
			return entities->get<player>(player_id);
		}

		entt::entity entity_manager::getPlayer()
		{
			return player_id;
		}

		void entity_manager::setPlayer(unsigned int id)
		{
			player_id = id;
		}

		entity_manager * entity_manager::getInstance()
		{
			return instance;
		}
	}
}