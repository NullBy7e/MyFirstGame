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

#include "animation_system.hpp"

namespace mfg
{
	namespace systems
	{
		AnimationSystem::AnimationSystem(EntityManager* entmgr) : entmgr(entmgr)
		{
		}

		thor::Animator<sf::Sprite, std::string>* AnimationSystem::getAnimator(entt::entity id)
		{
			if (auto it{ animators.find(id) }; it != std::end(animators))
			{
				return animators[id].get();
			}
			else
			{
				thor::Animator<sf::Sprite, std::string> animator;
				animators[id] = std::make_unique<thor::Animator<sf::Sprite, std::string>>(animator);

				return animators[id].get();
			}
		}

		void AnimationSystem::animate(sf::Time dt)
		{
			auto& entities = entmgr->getEntities();

			entities.view<ActiveAnimationComponent>().each([this, dt](auto entity, auto &active) {
				auto animator = this->getAnimator(entity);

				animator->animate(*active.animation->sprite);
				animator->update(dt);
			});
		}

		void AnimationSystem::stopAnimation(entt::entity entity)
		{
			auto animator = this->getAnimator(entity);
			animator->stopAnimation();
		}
	}
}