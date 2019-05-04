#include "GameState.hpp"
#include "LevelEditorGameState.hpp"
#include "../core/Window.hpp"
#include <imgui-SFML.h>

LevelEditorGameState::LevelEditorGameState(Window& window): GameState(window)
{
}

void LevelEditorGameState::handle_input()
{
	sf::Event event{};

	while(window_.poll_event(event))
	{
		ImGui::SFML::ProcessEvent(event);
	}

	ImGui::SFML::Update(window_.get(), window_.dt_);
}

void LevelEditorGameState::clear()
{
	window_.clear();
}

void LevelEditorGameState::update()
{
}

void LevelEditorGameState::draw()
{
	window_.draw(mapEditor_);
	ImGui::SFML::Render(window_.get());
}


