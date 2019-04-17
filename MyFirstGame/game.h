#pragma once

#include "window.h"

class Game
{
public:
	Game();
	~Game();

	void Load();
	void Loop();

	Window window_;
};
