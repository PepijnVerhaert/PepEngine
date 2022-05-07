#pragma once
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

		virtual int Play(const int id, const int volume) = 0;
		virtual void Pause(const int id, const int channel) = 0;
		virtual void Stop(const int id, const int channel) = 0;
		virtual void ProcessSound() = 0;
		virtual int Load(const std::string& file) = 0;
	};
}