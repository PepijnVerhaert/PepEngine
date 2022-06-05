#pragma once
#include <string>

namespace pep
{
	class BaseSoundService
	{
	public:
		BaseSoundService() = default;
		virtual ~BaseSoundService() = default;
		BaseSoundService(const BaseSoundService& other) = delete;
		BaseSoundService(BaseSoundService&& other) = delete;
		BaseSoundService& operator=(const BaseSoundService& other) = delete;
		BaseSoundService& operator=(BaseSoundService&& other) = delete;

		virtual void SetFilePath(const std::string& path) = 0;

		virtual void PlayEffect(const std::string& file, const int volume) = 0;
		virtual void PauseEffects() = 0;
		virtual void ResumeEffects() = 0;
		virtual void StopEffects() = 0;

		virtual void PlayMusic(const std::string& file, bool loop, const int volume, float fadeInSec = 0.f) = 0;
		virtual void PauseMusic() = 0;
		virtual void ResumeMusic() = 0;
		virtual void StopMusic(float fadeOutSec = 0.f) = 0;

		virtual void ProcessSound() = 0;
	};
}