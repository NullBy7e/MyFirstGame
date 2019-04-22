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

#include "entity.hpp"

namespace mfg {
	namespace components {
		EntityComponent::EntityComponent(
			float x,
			float y,
			float width,
			float height,
			float x_scale,
			float y_scale,
			float rotation,
			bool flipped_horizontally,
			sf::Sprite sprite)
			:
			x(x),
			y(y),
			width(width),
			height(height),
			x_scale(x_scale),
			y_scale(y_scale),
			rotation(rotation),
			flipped_horizontally(flipped_horizontally),
			sprite(sprite)
		{
		}

		void EntityComponent::setFacingLeft()
		{
			facing_right = false;
			facing_left = true;
		}

		void EntityComponent::setFacingRight()
		{
			facing_left = false;
			facing_right = true;
		}
	}
}