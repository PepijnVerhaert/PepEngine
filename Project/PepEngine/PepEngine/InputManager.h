#pragma once
#include "Singleton.h"
#include "InputHelper.h"
#include "ControllerManager.h"

#include <memory>

namespace pep
{
	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool QuitGame();
		void Update();
		bool IsControllerButtonActive(const ControllerButton& button, const ButtonState& state, unsigned int playerId) const;
	private:
		friend class Singleton<InputManager>;
		InputManager() = default;
		bool m_QuitGame = false;
		std::unique_ptr<ControllerManager> m_pControllerManager = std::make_unique<ControllerManager>();
	};

}
