/*
MIT License

Copyright (c) 2019 Youri de Mooij

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#include "entity_manager.hpp"
#include "../components/actor.hpp"
#include "../components/animation.hpp"
#include "../components/health.hpp"
#include "../components/position.hpp"

namespace mfg
{
	namespace managers
	{
		entt::entity EntityManager::createActor(
			const std::string& actor_name,
			const int          health,
			const bool         flipped_horizontally,
			const float        width,
			const float        height,
			const sf::Sprite&  sprite,
			const sf::Vector2f position
		)
		{
			const auto entity = entities_.create();

			entities_.assign<ActorComponent>(entity, actor_name);
			entities_.assign<AnimationComponent>(entity);
			entities_.assign<HealthComponent>(entity, health);
			entities_.assign<SpriteComponent>(entity, SpriteComponent(
				                                  flipped_horizontally,
				                                  width,
				                                  height,
				                                  sprite
			                                  ));
			entities_.assign<PositionComponent>(entity, position.x, position.y);

			return entity;
		}

		entt::registry& EntityManager::getEntities()
		{
			return entities_;
		}

		entt::entity EntityManager::getPlayer() const
		{
			return player_id_;
		}

		void EntityManager::setPlayer(const unsigned int id)
		{
			player_id_ = id;
		}
	}
}
