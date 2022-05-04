#pragma once

class BaseSoundService
{
public:
	BaseSoundService() = default;
	virtual ~BaseSoundService() = default;
	BaseSoundService(const BaseSoundService& other) = delete;
	BaseSoundService(BaseSoundService&& other) = delete;
	BaseSoundService& operator=(const BaseSoundService& other) = delete;
	BaseSoundService& operator=(BaseSoundService&& other) = delete;

	virtual int Play(const size_t id, const float volume) = 0;
	virtual void Pause(const size_t id, const int channel) = 0;
	virtual void Stop(const size_t id, const int channel) = 0;

protected:
	virtual void Load(const size_t id) = 0;
};