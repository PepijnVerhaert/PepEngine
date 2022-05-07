#pragma once
#include "BaseSoundService.h"

#include <queue>
#include <map>
#include <SDL_mixer.h>

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

		int Play(const int id, const int volume) override;
		void Pause(const int id, const int channel) override;
		void Stop(const int id, const int channel) override;
		void ProcessSound() override;
		int Load(const std::string& file) override;

		void Initialize();
	private:
		std::vector<Mix_Chunk*> m_Effects;
		std::map<std::string, size_t> m_LoadedEffects;



	};
}