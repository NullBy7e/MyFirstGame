#pragma once

#include "window.h"
#include "tmx/tmx_parser.hpp"

class Game
{
public:
	Game();
	~Game();

	void Load();
	void Loop();

	Window window_;
};
