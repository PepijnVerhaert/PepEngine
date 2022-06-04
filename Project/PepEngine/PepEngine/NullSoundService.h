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

		void SetFilePath(const std::string& ) override {};

		void PlayEffect(const std::string& , const int ) override {};
		void PauseEffects() override {};
		void ResumeEffects() override {};
		void StopEffects() override {};

		void PlayMusic(const std::string& , bool , const int , float ) override {};
		void PauseMusic() override {};
		void ResumeMusic() override {};
		void StopMusic(float ) override {};

		void ProcessSound() override {};
	};
}