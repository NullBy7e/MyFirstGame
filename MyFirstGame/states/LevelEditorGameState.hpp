#pragma once
#include "GameState.hpp"

class LevelEditorGameState final : public GameState
{
public:
	void handle_input(Window& window, float dt) override;
	void update(Window& window, float dt) override;
	void clear(Window& window) override;
	void draw(Window& window, float dt) override;
};