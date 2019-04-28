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

#pragma once

#include "../macros.hpp"

#include "../components/components.hpp"

#include "../components/actor.hpp"
#include "../components/animation.hpp"
#include "../components/health.hpp"
#include "../components/sprite.hpp"
#include "../components/position.hpp"

using namespace mfg::components;

namespace mfg
{
	namespace managers
	{
		class EntityManager
		{
		public:
			EntityManager();
			~EntityManager();

			entt::entity createActor(
				const std::string& actor_name,
				const int health,
				const bool flipped_horizontally,
				const float width,
				const float height,
				const sf::Sprite sprite,
				const sf::Vector2f position
			);

			entt::registry& getEntities();

			entt::entity getPlayer();
			void setPlayer(unsigned int id);
		private:
			entt::registry entities;
			entt::entity player_id = -1;
		};
	}
}