#pragma once
#include "InputHelper.h"
#include "BaseCommand.h"
#include <memory>

namespace pep
{
	class BaseInputService
	{
	public:
		BaseInputService() = default;
		virtual ~BaseInputService() = default;
		BaseInputService(const BaseInputService& other) = delete;
		BaseInputService(BaseInputService&& other) = delete;
		BaseInputService& operator=(const BaseInputService& other) = delete;
		BaseInputService& operator=(BaseInputService&& other) = delete;

		virtual bool QuitGame() = 0;
		virtual void Update() = 0;
		virtual bool IsControllerButtonActive(const ControllerButton& button, const ButtonState& state, unsigned int playerId) const = 0;
		virtual bool IsKeyboardKeyActive(const KeyboardKey& key, const ButtonState& state) const = 0;

		virtual void AddControllerCommand(const ControllerButton& button, const ButtonState& state, std::shared_ptr<BaseCommand> command, unsigned int playerId) = 0;
		virtual void AddKeyboardCommand(const KeyboardKey& key, const ButtonState& state, std::shared_ptr<BaseCommand> command) = 0;

		virtual void RemoveControllerCommand(const ControllerButton& button, const ButtonState& state, unsigned int playerId) = 0;
		virtual void RemoveKeyboardCommand(const KeyboardKey& key, const ButtonState& state) = 0;
	};
}