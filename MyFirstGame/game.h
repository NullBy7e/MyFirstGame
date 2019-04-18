#pragma once

#include "window.h"
#include "tmx/tmx_parser.hpp"
#include "texture_manager.hpp"

class Game
{
public:
	void Load();
	void Loop();
	void DrawXYChart();

	Window window_;
};
