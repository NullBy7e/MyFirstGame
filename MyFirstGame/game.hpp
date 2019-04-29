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

#include "window.hpp"

#include "tmx/tmx_parser.hpp"

#include "components/components.hpp"

#include "managers/texture_manager.hpp"
#include "managers/map_manager.hpp"

#include "map_renderer.hpp"
#include "player_data.hpp"

#ifdef DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#endif

using namespace mfg;
using namespace managers;
using namespace components;

namespace mfg
{
	namespace core
	{
		class Game
		{
		public:
			Game();

			void        updateViewport();
			player_data createPlayerData();

			void loop();
			void clear();
			void display();
		private:
			sf::Time restartClock();
			float    getElapsedFrameTime() const;

			Window   window_;
			Viewport viewport_;

			sf::Vector2i screen_dimensions_;

			sf::Clock clock_;

			TextureManager texmgr_;
			MapManager     mapmgr_;
		};
	}
}
