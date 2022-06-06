#include "PepEnginePCH.h"
#include "InputService.h"
#include "backends/imgui_impl_sdl.h"

using namespace pep;

bool pep::InputService::QuitGame()
{
	return m_QuitGame;
}

void InputService::Update()
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			m_QuitGame = true;
		}
		//process events for IMGUI
		ImGui_ImplSDL2_ProcessEvent(&e);
	}
	if(m_pControllerManager)
		m_pControllerManager->Update();
	if (m_pKeyboardManager)
		m_pKeyboardManager->Update();
}

bool pep::InputService::IsControllerButtonActive(const ControllerButton& button, const ButtonState& state, unsigned int playerId) const
{
	return m_pControllerManager->IsButtonActive(button, state, playerId);
}

bool pep::InputService::IsKeyboardKeyActive(const KeyboardKey& key, const ButtonState& state) const
{
	return m_pKeyboardManager->IsKeyActive(key, state);
}

void pep::InputService::AddControllerCommand(const ControllerButton& button, const ButtonState& state, std::shared_ptr<BaseCommand> command, unsigned int playerId)
{
	m_pControllerManager->AddCommand(button, state, command, playerId);
}

void pep::InputService::AddKeyboardCommand(const KeyboardKey& key, const ButtonState& state, std::shared_ptr<BaseCommand> command)
{
	m_pKeyboardManager->AddCommand(key, state, command);
}

void pep::InputService::RemoveControllerCommand(const ControllerButton& button, const ButtonState& state, unsigned int playerId)
{
	m_pControllerManager->RemoveCommand(button, state, playerId);
}

void pep::InputService::RemoveKeyboardCommand(const KeyboardKey& key, const ButtonState& state)
{
	m_pKeyboardManager->RemoveCommand(key, state);
}
