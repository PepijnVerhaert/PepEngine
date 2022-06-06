#pragma once
#include "BaseInputService.h"

namespace pep
{
	class NullInputService final : public BaseInputService
	{
	public:
		NullInputService() = default;
		~NullInputService() = default;
		NullInputService(const NullInputService& other) = delete;
		NullInputService(NullInputService&& other) = delete;
		NullInputService& operator=(const NullInputService& other) = delete;
		NullInputService& operator=(NullInputService&& other) = delete;

		bool QuitGame() override { return false; };
		void Update() override {};
		bool IsControllerButtonActive(const ControllerButton& , const ButtonState& , unsigned int ) const override { return false; };
		bool IsKeyboardKeyActive(const KeyboardKey& , const ButtonState& ) const override { return false; };

		void AddControllerCommand(const ControllerButton& , const ButtonState& , std::shared_ptr<BaseCommand> , unsigned int ) override {};
		void AddKeyboardCommand(const KeyboardKey& , const ButtonState& , std::shared_ptr<BaseCommand> ) override {};

		void RemoveControllerCommand(const ControllerButton& , const ButtonState& , unsigned int ) override {};
		void RemoveKeyboardCommand(const KeyboardKey& , const ButtonState& ) override {};
	};
}