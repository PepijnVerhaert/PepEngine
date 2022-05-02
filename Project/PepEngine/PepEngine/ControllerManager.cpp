#include "PepEnginePCH.h"
#include "ControllerManager.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <XInput.h>
#pragma comment(lib, "xinput.lib")

#include "GameTime.h"

using namespace pep;

//XINPUT IMPLEMENTATION
class pep::ControllerManager::ControllerManagerImpl
{
public:
	ControllerManagerImpl()
		: m_CurrentStates{}
		, m_PreviousStates{}
		, m_ButtonsPressedThisFrame{}
		, m_ButtonsReleasedThisFrame{}
		, m_ActiveControllers{}
		, m_activityCheckTimeAcc{0.f}
		, m_activityCheckTimeMax{1.5f}
	{
		m_CurrentStates.resize(XUSER_MAX_COUNT, {});
		m_PreviousStates.resize(XUSER_MAX_COUNT, {});
		m_ButtonsPressedThisFrame.resize(XUSER_MAX_COUNT, {});
		m_ButtonsReleasedThisFrame.resize(XUSER_MAX_COUNT, {});
		m_ActiveControllers.resize(XUSER_MAX_COUNT, false);

		for (size_t i = 0; i < XUSER_MAX_COUNT; ++i)
		{
			ZeroMemory(&m_CurrentStates[i], sizeof(XINPUT_STATE));
			ZeroMemory(&m_PreviousStates[i], sizeof(XINPUT_STATE));
		}
	}

	void Update()
	{
		//update timer
		m_activityCheckTimeAcc -= GameTime::GetInstance().GetDeltaTime();

		//check for each controller
		for (size_t i = 0; i < XUSER_MAX_COUNT; ++i)
		{
			//check if controller is active or it's time to check inactive controllers
			if (!m_ActiveControllers[i] && m_activityCheckTimeAcc > 0.f)
			{
				continue;
			}

			//copy current to previous and clear current
			CopyMemory(&m_PreviousStates[i], &m_CurrentStates[i], sizeof(XINPUT_STATE));
			ZeroMemory(&m_CurrentStates[i], sizeof(XINPUT_STATE));
			//get current
			auto result = XInputGetState(DWORD(i), &m_CurrentStates[i]);

			//check if controller is connected
			if (result == ERROR_SUCCESS)
			{
				//set button states correct
				auto buttonChanges = m_CurrentStates[i].Gamepad.wButtons ^ m_PreviousStates[i].Gamepad.wButtons;
				m_ButtonsPressedThisFrame[i] = buttonChanges & m_CurrentStates[i].Gamepad.wButtons;
				m_ButtonsReleasedThisFrame[i] = buttonChanges & (~m_CurrentStates[i].Gamepad.wButtons);

				//if it was time to check set controller to active
				if (m_activityCheckTimeAcc <= 0.f)
				{
					m_ActiveControllers[i] = true;
				}
			}
			//if failed no controller is connected
			else
			{
				m_ActiveControllers[i] = false;
				//clear memory so we dont keep getting last input
				ZeroMemory(&m_CurrentStates[i], sizeof(XINPUT_STATE));
				ZeroMemory(&m_PreviousStates[i], sizeof(XINPUT_STATE));
			}
		}

		//if it was time to check reset timer
		if (m_activityCheckTimeAcc <= 0.f)
		{
			m_activityCheckTimeAcc = m_activityCheckTimeMax;
		}
	}

	bool IsDown(const ControllerButton& button, size_t playerId) const 
	{ 
		if (playerId >= XUSER_MAX_COUNT) return false;
		if (!m_ActiveControllers[playerId]) return false;
		return m_CurrentStates[playerId].Gamepad.wButtons & static_cast<unsigned int>(button); 
	};
	bool IsPressedThisFrame(const ControllerButton& button, size_t playerId) const
	{ 
		if (playerId >= XUSER_MAX_COUNT) return false;
		if (!m_ActiveControllers[playerId]) return false;
		return m_ButtonsPressedThisFrame[playerId] & static_cast<unsigned int>(button);
	};
	bool IsReleasedThisFrame(const ControllerButton& button, size_t playerId) const
	{ 
		if (playerId >= XUSER_MAX_COUNT) return false;
		if (!m_ActiveControllers[playerId]) return false;
		return m_ButtonsReleasedThisFrame[playerId] & static_cast<unsigned int>(button);
	};

private:
	std::vector<XINPUT_STATE> m_CurrentStates;
	std::vector <XINPUT_STATE> m_PreviousStates;
	std::vector <WORD> m_ButtonsPressedThisFrame;
	std::vector <WORD> m_ButtonsReleasedThisFrame;
	std::vector<bool> m_ActiveControllers;

	float m_activityCheckTimeAcc;
	float m_activityCheckTimeMax;
};


pep::ControllerManager::ControllerManager()
	: m_PressedCommands{}
	, m_DownCommands{}
	, m_ReleasedCommands{}
	, m_pImpl{}
	, m_MaxControllers{4}
{
	m_pImpl = new ControllerManagerImpl;
	m_PressedCommands.resize(m_MaxControllers, {});
	m_DownCommands.resize(m_MaxControllers, {});
	m_ReleasedCommands.resize(m_MaxControllers, {});
}

pep::ControllerManager::~ControllerManager()
{
	delete m_pImpl;
}

void pep::ControllerManager::Update()
{
	//update commands
	m_pImpl->Update();

	//execute commands
	for (size_t i = 0; i < m_MaxControllers; ++i)
	{
		for (const auto& command : m_DownCommands[i])
		{
			if (m_pImpl->IsDown(command.first, i))
			{
				command.second->Execute();
			}
		}

		for (const auto& command : m_PressedCommands[i])
		{
			if (m_pImpl->IsPressedThisFrame(command.first, i))
			{
				command.second->Execute();
			}
		}

		for (const auto& command : m_ReleasedCommands[i])
		{
			if (m_pImpl->IsReleasedThisFrame(command.first, i))
			{
				command.second->Execute();
			}
		}
	}
}

void pep::ControllerManager::AddCommand(const ControllerButton& button, const ButtonState& state, std::shared_ptr<BaseCommand> command, unsigned int playerId)
{
	switch (state)
	{
	case pep::ButtonState::Down:
		m_DownCommands[playerId].emplace(std::make_pair(button, std::move(command)));
		break;
	case pep::ButtonState::PressedThisFrame:
		m_PressedCommands[playerId].emplace(std::make_pair(button, std::move(command)));
		break;
	case pep::ButtonState::ReleasedThisFrame:
		m_ReleasedCommands[playerId].emplace(std::make_pair(button, std::move(command)));
		break;
	}
}

void pep::ControllerManager::RemoveCommand(const ControllerButton& button, const ButtonState& state, unsigned int playerId)
{
	switch (state)
	{
	case pep::ButtonState::Down:
		m_DownCommands[playerId].erase(button);
		break;
	case pep::ButtonState::PressedThisFrame:
		m_PressedCommands[playerId].erase(button);
		break;
	case pep::ButtonState::ReleasedThisFrame:
		m_ReleasedCommands[playerId].erase(button);
		break;
	}
}
bool pep::ControllerManager::IsButtonActive(const ControllerButton& button, const ButtonState& state, unsigned int playerId) const
{
	switch (state)
	{
	case pep::ButtonState::Down:
		return m_pImpl->IsDown(button, playerId);
		break;
	case pep::ButtonState::PressedThisFrame:
		return m_pImpl->IsPressedThisFrame(button, playerId);
		break;
	case pep::ButtonState::ReleasedThisFrame:
		return m_pImpl->IsReleasedThisFrame(button, playerId);
		break;
	default:
		return false;
		break;
	}
}
