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

		int Play(const int id, const int volume) override;
		void Pause(const int id, const int channel) override;
		void Stop(const int id, const int channel) override;
		void ProcessSound() override;
		int Load(const std::string& file) override;

	private:
		BaseSoundService* m_pActualSoundService;
	};
}