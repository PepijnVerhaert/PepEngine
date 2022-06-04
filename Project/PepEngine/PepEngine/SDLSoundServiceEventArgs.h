#pragma once
#include "EventArgs.h"
#include <string>

namespace pep
{
	class PlayEffectEventArgs final : public EventArgs
	{
	public:
		PlayEffectEventArgs(const std::string& file, const int volume)
			: m_File{file}
			, m_Volume{volume}
		{}
		~PlayEffectEventArgs() = default;

		const std::string& GetFile() const
		{
			return m_File;
		}
		int GetVolume() const
		{
			return m_Volume;
		}
	private:
		std::string m_File;
		int m_Volume;
	};

	class PlayMusicEventArgs final : public EventArgs
	{
	public:
		PlayMusicEventArgs(const std::string& file, bool loop, const int volume, float fadeInSec = 0.f)
			: m_File{ file }
			, m_Loop{ loop }
			, m_Volume{ volume }
			, m_FadeInSec{ fadeInSec }
		{}
		~PlayMusicEventArgs() = default;

		const std::string& GetFile() const
		{
			return m_File;
		}
		bool GetLoop() const
		{
			return m_Loop;
		}
		int GetVolume() const
		{
			return m_Volume;
		}
		float GetFadeInSec() const
		{
			return m_FadeInSec;
		}
	private:
		std::string m_File;
		float m_FadeInSec;
		int m_Volume;
		bool m_Loop;
	};

	class StopMusicEventArgs final : public EventArgs
	{
	public:
		StopMusicEventArgs(float fadeOutSec)
			: m_FadeOutSec{ fadeOutSec}
		{}
		~StopMusicEventArgs() = default;
		float GetFadeOutSec() const
		{
			return m_FadeOutSec;
		}
	private:
		float m_FadeOutSec;
	};
}