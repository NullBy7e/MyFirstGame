#pragma once

class Window;

class GameState  // NOLINT(hicpp-special-member-functions, cppcoreguidelines-special-member-functions)
{
public:
	virtual ~GameState() = default;

	virtual void handle_input(Window& window, float dt) {};
	virtual void update(Window& window, float dt) {};
	virtual void clear(Window& window) {};
	virtual void draw(Window& window, float dt) {};
};

