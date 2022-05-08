#include "PepEnginePCH.h"
#include "LoggingSoundService.h"

#include <iostream>

using namespace pep;

LoggingSoundService::LoggingSoundService(BaseSoundService* pActualSoundService)
	:m_pActualSoundService(pActualSoundService)
{
	std::cout << "Logging sound system of type: " << typeid(*m_pActualSoundService).name() << ".\n";
}

void pep::LoggingSoundService::SetFilePath(const std::string& path)
{
	std::cout << "Set file path to \"" << path << "\".\n";
	m_pActualSoundService->SetFilePath(path);
}

void pep::LoggingSoundService::PlayEffect(const std::string& file, const int volume)
{
	std::cout << "Playing effect \"" << file << "\" at volume " << volume << ".\n";
	m_pActualSoundService->PlayEffect(file, volume);
}

void pep::LoggingSoundService::PauseEffects()
{
	std::cout << "Pausing all sound effects.\n";
	m_pActualSoundService->PauseEffects();
}

void pep::LoggingSoundService::ResumeEffects()
{
	std::cout << "Resuming all sound effects.\n";
	m_pActualSoundService->ResumeEffects();
}

void pep::LoggingSoundService::StopEffects()
{
	std::cout << "Stopping all sound effects.\n";
	m_pActualSoundService->StopEffects();
}

void pep::LoggingSoundService::PlayMusic(const std::string& file, bool loop, const int volume, float fadeInSec)
{
	std::cout << "Playing music \"" << file << "\" at volume " << volume << ", with a fade-in time of " << fadeInSec << " seconds and loop set to " << loop << ".\n";
	m_pActualSoundService->PlayMusic(file, loop, volume, fadeInSec);
}

void pep::LoggingSoundService::PauseMusic()
{
	std::cout << "Pausing music.\n";
	m_pActualSoundService->PauseMusic();
}

void pep::LoggingSoundService::ResumeMusic()
{
	std::cout << "Resuming music.\n";
	m_pActualSoundService->ResumeMusic();
}

void pep::LoggingSoundService::StopMusic(float fadeOutSec)
{
	std::cout << "Stopping music with a fade-out time of " << fadeOutSec << " seconds.\n";
	m_pActualSoundService->StopMusic(fadeOutSec);
}

void pep::LoggingSoundService::ProcessSound()
{
	m_pActualSoundService->ProcessSound();
}