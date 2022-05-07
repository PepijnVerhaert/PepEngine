#include "PepEnginePCH.h"
#include "LoggingSoundService.h"

#include <iostream>

using namespace pep;

LoggingSoundService::LoggingSoundService(BaseSoundService* pActualSoundService)
	:m_pActualSoundService(pActualSoundService)
{
	std::cout << "Logging sound system of type: " << typeid(*m_pActualSoundService).name() << ".\n";
}

int LoggingSoundService::Play(const int id, const int volume)
{
	std::cout << "Playing " << id << " at volume " << volume << ".\n";
	return m_pActualSoundService->Play(id, volume);
}

void LoggingSoundService::Pause(const int id, const int channel)
{
	std::cout << "Pausing " << id << " on channel " << channel << ".\n";
	m_pActualSoundService->Pause(id, channel);
}

void LoggingSoundService::Stop(const int id, const int channel)
{
	std::cout << "Stopping " << id << " on channel " << channel << ".\n";
	m_pActualSoundService->Stop(id, channel);
}

void pep::LoggingSoundService::ProcessSound()
{
	m_pActualSoundService->ProcessSound();
}

int LoggingSoundService::Load(const std::string& file)
{
	int id = m_pActualSoundService->Load(file);
	if(id != -1)
		std::cout << "Loaded \"" << file << "\" to id " << id << ".\n";
	else
		std::cout << "Failed to load \"" << file << "\" id returned " << id << ".\n";
	return id;
}
