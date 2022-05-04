#pragma once
#include "BaseSoundService.h"

class NullSoundService final : public BaseSoundService
{
public:
	NullSoundService() = default;
	~NullSoundService() = default;
	NullSoundService(const NullSoundService& other) = delete;
	NullSoundService(NullSoundService&& other) = delete;
	NullSoundService& operator=(const NullSoundService& other) = delete;
	NullSoundService& operator=(NullSoundService&& other) = delete;

	int Play(const size_t id, const float volume) override {};
	void Pause(const size_t id, const int channel) override {};
	void Stop(const size_t id, const int channel) override {};

private:
	void Load(const size_t id) override {};
};