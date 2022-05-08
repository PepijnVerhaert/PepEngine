#pragma once

#include "BaseSoundService.h"

namespace pep
{

	class LoggingSoundService final : public BaseSoundService
	{
	public:
		LoggingSoundService(BaseSoundService* pActualSoundService);
		~LoggingSoundService() = default;
		LoggingSoundService(const LoggingSoundService& other) = delete;
		LoggingSoundService(LoggingSoundService&& other) = delete;
		LoggingSoundService& operator=(const LoggingSoundService& other) = delete;
		LoggingSoundService& operator=(LoggingSoundService&& other) = delete;
		
		void SetFilePath(const std::string& path) override;

		void PlayEffect(const std::string& file, const int volume) override;
		void PauseEffects() override;
		void ResumeEffects() override;
		void StopEffects() override;

		void PlayMusic(const std::string& file, bool loop, const int volume, float fadeInSec = 0.f) override;
		void PauseMusic() override;
		void ResumeMusic() override;
		void StopMusic(float fadeOutSec = 0.f) override;

		void ProcessSound() override;
	private:
		BaseSoundService* m_pActualSoundService;
	};
}