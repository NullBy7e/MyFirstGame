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

#include "MFG.hpp"

#include "window.hpp"
#include "tmx/tmx_parser.hpp"

#include "registries/registry.hpp"
#include "utils/types.hpp"

#include "caching/cache.hpp"
#include "components/components.hpp"

using namespace mfg;
using namespace mfg::registries;
using namespace mfg::caching;
using namespace mfg::managers;
using namespace mfg::events;

namespace mfg {
	namespace core
	{
		class game
		{
		public:
			game();

			void draw();
			void drawTiles();
			void drawEntities();

			void updateViewport();
			void createPlayer();

			void loop();

		private:
			std::unique_ptr<window> window;

			sf::Vector2i screen_dimensions;

			sf::View viewport;
			sf::Vector2f viewport_dimensions;
			int viewport_tile_width;
			int viewport_tile_height;
		};
	}
}