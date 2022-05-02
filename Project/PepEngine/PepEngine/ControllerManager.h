#pragma once
#include <memory>
#include <map>
#include <vector>

#include "InputHelper.h"
#include "BaseCommand.h"

namespace pep
{
	class ControllerManager final
	{
	public:
		ControllerManager();
		~ControllerManager();

		void Update();

		void AddCommand(const ControllerButton& button, const ButtonState& state, std::shared_ptr<BaseCommand> command, unsigned int playerId);
		void RemoveCommand(const ControllerButton& button, const ButtonState& state, unsigned int playerId);

		bool IsButtonActive(const ControllerButton& button, const ButtonState& state, unsigned int playerId) const;

	private:
		class ControllerManagerImpl;
		ControllerManagerImpl* m_pImpl;
		size_t m_MaxControllers;

		std::vector<std::map<ControllerButton, std::shared_ptr<BaseCommand>>> m_DownCommands;
		std::vector<std::map<ControllerButton, std::shared_ptr<BaseCommand>>> m_PressedCommands;
		std::vector<std::map<ControllerButton, std::shared_ptr<BaseCommand>>> m_ReleasedCommands;
	};
}