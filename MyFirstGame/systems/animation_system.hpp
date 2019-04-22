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

#include <type_traits>
#include <typeinfo>

#include <Thor/Animations.hpp>
#include <SFML/Graphics.hpp>

#include "entt/entt.hpp"

#include "../managers/entity_manager.hpp"
#include "../components/entity_animation.hpp"

using namespace mfg::managers;
using namespace mfg::components;

namespace mfg
{
	namespace systems
	{
		class animation_system
		{
		public:
			animation_system(entity_manager* entmgr);
			thor::Animator<sf::Sprite, std::string>* getAnimator(entt::entity id);

			void animate(sf::Time dt);
			void stopAnimation(entt::entity entity);

			entity_manager* entmgr;

			template<typename T>
			typename std::enable_if<std::is_base_of<entity_animation, T>::value, void>::type playAnimation(entt::entity, bool = false);

			template<typename T>
			typename std::enable_if<std::is_base_of<entity_animation, T>::value, void>::type addAnimation(entt::entity, T, sf::Time);

		private:
			std::map<entt::entity, std::unique_ptr<thor::Animator<sf::Sprite, std::string>>> animators;
			std::vector<std::unique_ptr<sf::Sprite>> animation_sprites;
		};

		template<typename T>
		inline typename std::enable_if<std::is_base_of<entity_animation, T>::value, void>::type animation_system::playAnimation(entt::entity entity, bool loop)
		{
			auto animator = getAnimator(entity);

			if (animator->isPlayingAnimation())
				return;

			T animation_component = entmgr->getEntities().get<T>(entity);
			entmgr->getEntities().assign_or_replace<active_animation>(entity, active_animation{ animation_component });

			animator->playAnimation(animation_component.name, loop);

			std::cout << "animation_system::playAnimation: " << animation_component.name << std::endl;
			return;
		}

		template<typename T>
		inline typename std::enable_if<std::is_base_of<entity_animation, T>::value, void>::type animation_system::addAnimation(entt::entity entity, T animation_component, sf::Time duration)
		{
			auto animator = getAnimator(entity);

			/* create new unique_ptr that points to the components sprite */
			animation_sprites.emplace_back(std::make_unique<sf::Sprite>(*animation_component.sprite));

			auto& sprite = animation_sprites.back();
			animation_component.sprite = sprite.get();

			/* add idle animation to the animator for the player */
			animator->addAnimation(animation_component.name, animation_component.frame, duration);

			/* add animation component to the player entity */
			entmgr->getEntities().assign<T>(entity, animation_component);

			return;
		}
	}
}