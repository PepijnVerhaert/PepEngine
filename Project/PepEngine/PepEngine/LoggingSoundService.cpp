#include "PepEnginePCH.h"
#include "LoggingSoundService.h"

#include <iostream>

LoggingSoundService::LoggingSoundService(BaseSoundService* pActualSoundService)
	:m_pActualSoundService(pActualSoundService)
{
	std::cout << "Logging sound system of type: " << typeid(*m_pActualSoundService).name() << ".\n";
}

int LoggingSoundService::Play(const size_t id, const float volume)
{
	std::cout << "Playing " << id << " at volume " << volume << ".\n";
	return m_pActualSoundService->Play(id, volume);
}

void LoggingSoundService::Pause(const size_t id, const int channel)
{
	std::cout << "Pausing " << id << " on channel " << channel << ".\n";
	m_pActualSoundService->Pause(id, channel);
}

void LoggingSoundService::Stop(const size_t id, const int channel)
{
	std::cout << "Stopping " << id << " on channel " << channel << ".\n";
	m_pActualSoundService->Stop(id, channel);
}

void LoggingSoundService::Load(const size_t)
{}
