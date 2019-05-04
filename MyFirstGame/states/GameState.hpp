#pragma once

class Window;

class GameState  // NOLINT(hicpp-special-member-functions, cppcoreguidelines-special-member-functions)
{
public:
	explicit GameState(Window& window): window_(window){};
	virtual ~GameState() = default;

	virtual void handle_input() {};
	virtual void update() {};
	virtual void clear() {};
	virtual void draw() {};

protected:
	Window& window_;
};

