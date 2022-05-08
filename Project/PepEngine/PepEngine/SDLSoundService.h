#pragma once
#include "BaseSoundService.h"

namespace pep
{

	class SDLSoundService final : public BaseSoundService
	{
	public:
		SDLSoundService();
		~SDLSoundService();
		SDLSoundService(const SDLSoundService& other) = delete;
		SDLSoundService(SDLSoundService&& other) = delete;
		SDLSoundService& operator=(const SDLSoundService& other) = delete;
		SDLSoundService& operator=(SDLSoundService&& other) = delete;

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

		void Initialize();
	private:
		class SDLSoundServiceImpl;
		SDLSoundServiceImpl* m_pImpl;
	};
}