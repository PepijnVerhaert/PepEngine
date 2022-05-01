#include "PepEnginePCH.h"
#include "ControllerManager.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <XInput.h>
#pragma comment(lib, "xinput.lib")

#include "Time.h"

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
		m_activityCheckTimeAcc -= Time::GetInstance().GetDeltaTime();

		for (size_t i = 0; i < XUSER_MAX_COUNT; ++i)
		{
			if (!m_ActiveControllers[i] && m_activityCheckTimeAcc > 0.f)
			{
				continue;
			}

			CopyMemory(&m_PreviousStates, &m_CurrentStates, sizeof(XINPUT_STATE));
			ZeroMemory(&m_CurrentStates, sizeof(XINPUT_STATE));
			auto result = XInputGetState(DWORD(i), &m_CurrentStates[i]);

			if (result == ERROR_SUCCESS)
			{
				auto buttonChanges = m_CurrentStates[i].Gamepad.wButtons ^ m_PreviousStates[i].Gamepad.wButtons;
				m_ButtonsPressedThisFrame[i] = buttonChanges & m_CurrentStates[i].Gamepad.wButtons;
				m_ButtonsReleasedThisFrame[i] = buttonChanges & (~m_CurrentStates[i].Gamepad.wButtons);

				if (m_activityCheckTimeAcc <= 0.f)
				{
					m_ActiveControllers[i] = true;
				}
			}
			else
			{
				m_ActiveControllers[i] = false;
				ZeroMemory(&m_CurrentStates[i], sizeof(XINPUT_STATE));
				ZeroMemory(&m_PreviousStates[i], sizeof(XINPUT_STATE));
			}
		}

		if (m_activityCheckTimeAcc <= 0.f)
		{
			m_activityCheckTimeAcc = m_activityCheckTimeMax;
		}
	}

	bool IsDown(const ControllerButton& button, unsigned int playerId) const 
	{ 
		if (playerId >= XUSER_MAX_COUNT) return false;
		if (!m_ActiveControllers[playerId]) return false;
		return m_CurrentStates[playerId].Gamepad.wButtons & static_cast<unsigned int>(button); 
	};
	bool IsPressed(const ControllerButton& button, unsigned int playerId) const 
	{ 
		if (playerId >= XUSER_MAX_COUNT) return false;
		if (!m_ActiveControllers[playerId]) return false;
		return m_ButtonsPressedThisFrame[playerId] & static_cast<unsigned int>(button);
	};
	bool IsReleased(const ControllerButton& button, unsigned int playerId) const 
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
{
	m_PressedCommands.resize(4, {});
	m_DownCommands.resize(4, {});
	m_ReleasedCommands.resize(4, {});
}

pep::ControllerManager::~ControllerManager()
{
	delete m_pImpl;
}

void pep::ControllerManager::Update()
{
	m_pImpl->Update();
}

void pep::ControllerManager::AddCommand(const ControllerButton& button, const ButtonState& state, std::shared_ptr<BaseCommand> command, unsigned int playerId)
{
	switch (state)
	{
	case pep::ButtonState::Down:
		m_DownCommands[playerId].emplace(std::make_pair(button, std::move(command)));
		break;
	case pep::ButtonState::Pressed:
		m_PressedCommands[playerId].emplace(std::make_pair(button, std::move(command)));
		break;
	case pep::ButtonState::Released:
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
	case pep::ButtonState::Pressed:
		m_PressedCommands[playerId].erase(button);
		break;
	case pep::ButtonState::Released:
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
	case pep::ButtonState::Pressed:
		return m_pImpl->IsPressed(button, playerId);
		break;
	case pep::ButtonState::Released:
		return m_pImpl->IsReleased(button, playerId);
		break;
	default:
		return false;
		break;
	}
}
