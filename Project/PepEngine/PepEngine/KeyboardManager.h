#pragma once
#include <memory>
#include <map>
#include <vector>

#include "InputHelper.h"
#include "BaseCommand.h"

namespace pep
{
	class KeyboardManager final
	{
	public:
		KeyboardManager();
		~KeyboardManager();

		void Update();

		void AddCommand(const KeyboardKey& key, const ButtonState& state, std::shared_ptr<BaseCommand> command);
		void RemoveCommand(const KeyboardKey& key, const ButtonState& state);

		bool IsKeyActive(const KeyboardKey& key, const ButtonState& state) const;

	private:
		class KeyboardManagerImpl;
		KeyboardManagerImpl* m_pImpl;

		std::map<KeyboardKey, std::shared_ptr<BaseCommand>> m_DownCommands;
		std::map<KeyboardKey, std::shared_ptr<BaseCommand>> m_PressedCommands;
		std::map<KeyboardKey, std::shared_ptr<BaseCommand>> m_ReleasedCommands;
	};
}