#include "GameState.hpp"
#include "LevelEditorGameState.hpp"
#include "../core/Window.hpp"
#include <imgui-SFML.h>
#include <imgui.h>

LevelEditorGameState::LevelEditorGameState(Window& window): GameState(window)
{
	ImGui::SFML::Init(window.get());
	ImGui::StyleColorsDark();
	ImGui::GetIO().FontGlobalScale = 1.5f;
}

LevelEditorGameState::~LevelEditorGameState()
{
	ImGui::SFML::Shutdown();
}

void LevelEditorGameState::handle_input()
{
	sf::Event event{};

	while(window_.poll_event(event))
	{
		ImGui::SFML::ProcessEvent(event);
	}
}

void LevelEditorGameState::clear()
{
	window_.clear();
}

void LevelEditorGameState::update()
{
	ImGui::SFML::Update(window_.get(), window_.dt_);
}

void LevelEditorGameState::draw()
{
	window_.get().resetGLStates();

	mapEditor_.render(window_);

	ImGui::SFML::Render(window_.get());
}


