#pragma once
#include "GameState.hpp"
#include "../drawables/Grid.hpp"

class LevelEditorGameState final : public GameState
{
public:
	void handle_input(Window& window, float dt) override;
	void update(Window& window, float dt) override;
	void clear(Window& window) override;
	void draw(Window& window, float dt) override;

private:

	Grid grid_{ {1280, 1024}, {64, 64} };
};
