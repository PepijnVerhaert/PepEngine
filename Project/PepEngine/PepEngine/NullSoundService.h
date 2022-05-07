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

		int Play(const int id, const int volume) override {};
		void Pause(const int id, const int channel) override {};
		void Stop(const int id, const int channel) override {};
		int Load(const std::string& file) override { return -1; };
	};
}