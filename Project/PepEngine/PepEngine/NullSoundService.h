#pragma once
#include "BaseSoundService.h"

namespace pep
{

	class NullSoundService final : public BaseSoundService
	{
	public:
		NullSoundService() = default;
		~NullSoundService() = default;
		NullSoundService(const NullSoundService& other) = delete;
		NullSoundService(NullSoundService&& other) = delete;
		NullSoundService& operator=(const NullSoundService& other) = delete;
		NullSoundService& operator=(NullSoundService&& other) = delete;

		void SetFilePath(const std::string& path) override {};

		void PlayEffect(const std::string& file, const int volume) override {};
		void PauseEffects() override {};
		void ResumeEffects() override {};
		void StopEffects() override {};

		void PlayMusic(const std::string& file, bool loop, const int volume, float fadeInSec = 0.f) override {};
		void PauseMusic() override {};
		void ResumeMusic() override {};
		void StopMusic(float fadeOutSec = 0.f) override {};

		void ProcessSound() override {};
	};
}