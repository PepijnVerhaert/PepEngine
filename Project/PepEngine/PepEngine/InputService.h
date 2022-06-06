#pragma once
#include "BaseInputService.h"
#include "InputHelper.h"
#include "ControllerManager.h"
#include "KeyboardManager.h"

#include <memory>

namespace pep
{
	class InputService final : public BaseInputService
	{
	public:
		InputService() = default;
		~InputService() = default;
		InputService(const InputService& other) = delete;
		InputService(InputService&& other) = delete;
		InputService& operator=(const InputService& other) = delete;
		InputService& operator=(InputService&& other) = delete;


		bool QuitGame();
		void Update();
		bool IsControllerButtonActive(const ControllerButton& button, const ButtonState& state, unsigned int playerId) const;
		bool IsKeyboardKeyActive(const KeyboardKey& key, const ButtonState& state) const;

		void AddControllerCommand(const ControllerButton& button, const ButtonState& state, std::shared_ptr<BaseCommand> command, unsigned int playerId);
		void AddKeyboardCommand(const KeyboardKey& key, const ButtonState& state, std::shared_ptr<BaseCommand> command);

		void RemoveControllerCommand(const ControllerButton& button, const ButtonState& state, unsigned int playerId);
		void RemoveKeyboardCommand(const KeyboardKey& key, const ButtonState& state);

	private:
		bool m_QuitGame = false;
		std::unique_ptr<ControllerManager> m_pControllerManager = std::make_unique<ControllerManager>();
		std::unique_ptr<KeyboardManager> m_pKeyboardManager = std::make_unique<KeyboardManager>();
	};
}
