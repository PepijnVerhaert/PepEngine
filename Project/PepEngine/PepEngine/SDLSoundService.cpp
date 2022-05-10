#include "PepEnginePCH.h"
#include "SDLSoundService.h"

#include "SDLSoundServiceEventArgs.h"

#include <queue>
#include <map>
#include <SDL_mixer.h>
#include <thread>
#include <mutex>

using namespace pep;

//SDL IMPLEMENTATION
class pep::SDLSoundService::SDLSoundServiceImpl
{
public:
	enum class SDLSoundQueueEvent
	{
		PlayEffect,
		PauseEffect,
		ResumeEffect,
		StopEffect,
		PlayMusic,
		PauseMusic,
		ResumeMusic,
		StopMusic
	};

	SDLSoundServiceImpl()
		:m_pEffects{}
		,m_pMusic{}
		,m_Path{""}
		,m_EventQueue{}
		,m_Mutex{}
		,m_QuitProcessing{false}
	{
	}

	~SDLSoundServiceImpl()
	{

		Mix_CloseAudio();
	}

	void AddToQueue(SDLSoundQueueEvent event, const EventArgs& args)
	{
		auto lock = std::scoped_lock(m_Mutex);
		m_EventQueue.push(std::make_pair(event, args));
	}

	void ProcessSound()
	{
		while (!m_QuitProcessing)
		{
			auto lock = std::scoped_lock(m_Mutex);
			if (m_EventQueue.size() > 0)
			{
				auto currentQueue = m_EventQueue;
			}

		}
	}

	void Initialize() 
	{
		Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096);

	}

	void SetFilePath(const std::string& path) 
	{
		m_Path = path;
	}

private:

	void PlayEffect(const std::string& file, const int volume)
	{
		auto fullPath = m_Path + file;
		if (m_pEffects.find(fullPath) == m_pEffects.end())
		{
			//file hasn't been loaded
			LoadEffect(file);
		}

		if (m_pEffects.find(fullPath) != m_pEffects.end())
		{
			int channel = Mix_PlayChannel(-1, m_pEffects.at(fullPath), 0);
			if (channel != -1)
			{
				int newVolume = int((float(volume) / 100.f) * float(MIX_MAX_VOLUME));
				if (newVolume < 0) newVolume = 0;
				Mix_Volume(channel, newVolume);
			}
		}
	}
	void PauseEffects()
	{
		Mix_Pause(-1);
	}
	void ResumeEffects()
	{
		Mix_Resume(-1);
	}
	void StopEffects()
	{
		Mix_HaltChannel(-1);
	}

	void PlayMusic(const std::string& file, bool loop, const int volume, float fadeInSec = 0.f)
	{
		auto fullPath = m_Path + file;
		if (m_pMusic.find(fullPath) == m_pMusic.end())
		{
			//file hasn't been loaded
			LoadMusic(file);
		}

		if (m_pMusic.find(fullPath) != m_pMusic.end())
		{
			int newVolume = int((float(volume) / 100.f) * float(MIX_MAX_VOLUME));
			if (newVolume < 0) newVolume = 0;
			Mix_VolumeMusic(newVolume);

			int newLoop = loop == true ? -1 : 0;

			int fadeInMs = int(fadeInSec * 1000.f);

			int channel = Mix_FadeInMusic(m_pMusic.at(fullPath), newLoop, fadeInMs);
		}
	}
	void PauseMusic()
	{
		Mix_PauseMusic();
	}
	void ResumeMusic()
	{
		Mix_ResumeMusic();
	}
	void StopMusic(float fadeOutSec = 0.f) 
	{
		int fadeOutMs = int(fadeOutSec * 1000.f);
		Mix_FadeOutMusic(fadeOutMs);
	}

	void LoadEffect(const std::string& file)
	{
		auto fullPath = m_Path + file;
		if (m_pEffects.find(fullPath) == m_pEffects.end())
		{
			//file hasn't been loaded
			auto newEffect = Mix_LoadWAV(fullPath.c_str());
			if (newEffect)
			{
				//effect was loaded correctly
				m_pEffects.insert(std::make_pair(fullPath, newEffect));
			}
		}
	}
	void LoadMusic(const std::string& file)
	{
		auto fullPath = m_Path + file;
		if (m_pMusic.find(fullPath) == m_pMusic.end())
		{
			//file hasn't been loaded
			auto newMusic = Mix_LoadMUS(fullPath.c_str());
			if (newMusic)
			{
				//music was loaded correctly
				m_pMusic.insert(std::make_pair(fullPath, newMusic));
			}
		}
	}

	std::map<std::string, Mix_Chunk*> m_pEffects;
	std::map<std::string, Mix_Music*> m_pMusic;

	std::queue<std::pair<SDLSoundQueueEvent, const EventArgs>> m_EventQueue;
	std::mutex m_Mutex;

	std::string m_Path;

	bool m_QuitProcessing;
};


pep::SDLSoundService::SDLSoundService()
	:m_pImpl{nullptr}
{
	m_pImpl = new SDLSoundServiceImpl;
}

pep::SDLSoundService::~SDLSoundService()
{
	delete m_pImpl;
}

void pep::SDLSoundService::SetFilePath(const std::string& path)
{
	m_pImpl->SetFilePath(path);
}

void pep::SDLSoundService::PlayEffect(const std::string& file, const int volume)
{
	PlayEffectEventArgs e{ file, volume };
	m_pImpl->AddToQueue(SDLSoundServiceImpl::SDLSoundQueueEvent::PlayEffect, e);
}

void pep::SDLSoundService::PauseEffects()
{
	EventArgs e{};
	m_pImpl->AddToQueue(SDLSoundServiceImpl::SDLSoundQueueEvent::PauseEffect, e);
}

void pep::SDLSoundService::ResumeEffects()
{
	EventArgs e{};
	m_pImpl->AddToQueue(SDLSoundServiceImpl::SDLSoundQueueEvent::ResumeEffect, e);
}

void pep::SDLSoundService::StopEffects()
{
	EventArgs e{};
	m_pImpl->AddToQueue(SDLSoundServiceImpl::SDLSoundQueueEvent::StopEffect, e);
}

void pep::SDLSoundService::PlayMusic(const std::string& file, bool loop, const int volume, float fadeInSec)
{
	PlayMusicEventArgs e{ file, loop, volume, fadeInSec };
	m_pImpl->AddToQueue(SDLSoundServiceImpl::SDLSoundQueueEvent::PlayMusic, e);
}

void pep::SDLSoundService::PauseMusic()
{
	EventArgs e{};
	m_pImpl->AddToQueue(SDLSoundServiceImpl::SDLSoundQueueEvent::PauseMusic, e);
}

void pep::SDLSoundService::ResumeMusic()
{
	EventArgs e{};
	m_pImpl->AddToQueue(SDLSoundServiceImpl::SDLSoundQueueEvent::ResumeMusic, e);
}

void pep::SDLSoundService::StopMusic(float fadeOutSec)
{
	StopMusicEventArgs e{ fadeOutSec };
	m_pImpl->AddToQueue(SDLSoundServiceImpl::SDLSoundQueueEvent::StopMusic, e);
}

void pep::SDLSoundService::ProcessSound()
{
	m_pImpl->ProcessSound();
}

void pep::SDLSoundService::Initialize()
{
	m_pImpl->Initialize();
}