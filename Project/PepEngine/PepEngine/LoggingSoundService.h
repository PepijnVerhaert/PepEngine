#pragma once

#include "BaseSoundService.h"

class LoggingSoundService final : public BaseSoundService
{
public:
	LoggingSoundService(BaseSoundService* pActualSoundService);
	~LoggingSoundService() = default;
	LoggingSoundService(const LoggingSoundService& other) = delete;
	LoggingSoundService(LoggingSoundService&& other) = delete;
	LoggingSoundService& operator=(const LoggingSoundService& other) = delete;
	LoggingSoundService& operator=(LoggingSoundService&& other) = delete;

	int Play(const size_t id, const float volume) override;
	void Pause(const size_t id, const int channel) override;
	void Stop(const size_t id, const int channel) override;

private:
	void Load(const size_t id) override;

	BaseSoundService* m_pActualSoundService;
};