#include "PepEnginePCH.h"
#include "KeyboardManager.h"

#include "PepEnginePCH.h"
#include "KeyboardManager.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <XInput.h>
#pragma comment(lib, "xinput.lib")

#include "GameTime.h"

using namespace pep;

//XINPUT IMPLEMENTATION
class pep::KeyboardManager::KeyboardManagerImpl
{
public:
	KeyboardManagerImpl()
		:m_pCurrentState{nullptr}
		,m_pPreviousState{nullptr}
		,m_pKeyboardState0{new BYTE[256]}
		,m_pKeyboardState1{new BYTE[256]}
		,m_IsCurrentState0{true}
	{
	}

	~KeyboardManagerImpl()
	{
		delete[] m_pKeyboardState0;
		delete[] m_pKeyboardState1;
	}

	void Update()
	{
		//Get Current KeyboardState and set Old KeyboardState
		BOOL getKeyboardResult;
		if (m_IsCurrentState0)
		{
			getKeyboardResult = GetKeyboardState(m_pKeyboardState1);
			m_pPreviousState = m_pKeyboardState0;
			m_pCurrentState = m_pKeyboardState1;
		}
		else
		{
			getKeyboardResult = GetKeyboardState(m_pKeyboardState0);
			m_pPreviousState = m_pKeyboardState1;
			m_pCurrentState = m_pKeyboardState0;
		}
		m_IsCurrentState0 = !m_IsCurrentState0;
	}

	bool IsDown(const KeyboardKey& key) const
	{
		return GetKeyState(static_cast<unsigned int>(key), true);
	};
	bool IsPressedThisFrame(const KeyboardKey& key) const
	{
		return GetKeyState(static_cast<unsigned int>(key), true) && !GetKeyState(static_cast<unsigned int>(key), false);
	};
	bool IsReleasedThisFrame(const KeyboardKey& key) const
	{
		return !GetKeyState(static_cast<unsigned int>(key), true) && GetKeyState(static_cast<unsigned int>(key), false);
	};

private:
	bool GetKeyState(const unsigned int key, bool checkCurrent) const
	{
		if (checkCurrent)
		{
			return (m_pCurrentState[key] & 0xF0) != 0;
		}
		else
		{
			return (m_pPreviousState[key] & 0xF0) != 0;
		}
	}

	PBYTE m_pCurrentState;
	PBYTE m_pPreviousState;
	PBYTE m_pKeyboardState0;
	PBYTE m_pKeyboardState1;
	bool m_IsCurrentState0;
};


pep::KeyboardManager::KeyboardManager()
	: m_PressedCommands{}
	, m_DownCommands{}
	, m_ReleasedCommands{}
	, m_pImpl{}
{
	m_pImpl = new KeyboardManagerImpl;
}

pep::KeyboardManager::~KeyboardManager()
{
	delete m_pImpl;
}

void pep::KeyboardManager::Update()
{
	//update commands
	m_pImpl->Update();

	//execute commands
	
	for (const auto& command : m_DownCommands)
	{
		if (m_pImpl->IsDown(command.first))
		{
			command.second->Execute();
		}
	}

	for (const auto& command : m_PressedCommands)
	{
		if (m_pImpl->IsPressedThisFrame(command.first))
		{
			command.second->Execute();
		}
	}

	for (const auto& command : m_ReleasedCommands)
	{
		if (m_pImpl->IsReleasedThisFrame(command.first))
		{
			command.second->Execute();
		}
	}
}

void pep::KeyboardManager::AddCommand(const KeyboardKey& key, const ButtonState& state, std::shared_ptr<BaseCommand> command)
{
	switch (state)
	{
	case pep::ButtonState::Down:
		m_DownCommands.emplace(std::make_pair(key, std::move(command)));
		break;
	case pep::ButtonState::PressedThisFrame:
		m_PressedCommands.emplace(std::make_pair(key, std::move(command)));
		break;
	case pep::ButtonState::ReleasedThisFrame:
		m_ReleasedCommands.emplace(std::make_pair(key, std::move(command)));
		break;
	}
}

void pep::KeyboardManager::RemoveCommand(const KeyboardKey& key, const ButtonState& state)
{
	switch (state)
	{
	case pep::ButtonState::Down:
		m_DownCommands.erase(key);
		break;
	case pep::ButtonState::PressedThisFrame:
		m_PressedCommands.erase(key);
		break;
	case pep::ButtonState::ReleasedThisFrame:
		m_ReleasedCommands.erase(key);
		break;
	}
}
bool pep::KeyboardManager::IsKeyActive(const KeyboardKey& key, const ButtonState& state) const
{
	switch (state)
	{
	case pep::ButtonState::Down:
		return m_pImpl->IsDown(key);
		break;
	case pep::ButtonState::PressedThisFrame:
		return m_pImpl->IsPressedThisFrame(key);
		break;
	case pep::ButtonState::ReleasedThisFrame:
		return m_pImpl->IsReleasedThisFrame(key);
		break;
	default:
		return false;
		break;
	}
}
