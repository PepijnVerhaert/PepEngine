#include "PepEnginePCH.h"
#include "SDLSoundService.h"

#include "SDLSoundServiceEventArgs.h"

#include <queue>
#include <map>
#include <SDL_mixer.h>
#include <thread>
#include <mutex>
#include <memory>
#include <atomic>
#include <condition_variable>

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
		,m_WorkQueue{}
		,m_PlayedSounds{}
		,m_Mutex{}
		,m_ConVar{}
		,m_Quit{false}
		,m_QueueThread{}
	{
		Initialize();
	}

	~SDLSoundServiceImpl()
	{
		m_Quit = true;
		ProcessSound();
		if (m_QueueThread.joinable())
			m_QueueThread.join();		
		for (auto& pChunk : m_pEffects)
		{
			Mix_FreeChunk(pChunk.second);
		}
		for (auto& pMus : m_pMusic)
		{
			Mix_FreeMusic(pMus.second);
		}
		Mix_CloseAudio();
	}

	void AddToQueue(SDLSoundQueueEvent event, std::shared_ptr<EventArgs> pArgs)
	{
		auto lock = std::scoped_lock(m_Mutex);
		m_EventQueue.push(std::make_pair(event, pArgs));
	}

	void ProcessSound()
	{
		m_ConVar.notify_all();
	}

	void Initialize()
	{
		Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 1, 4096);
		m_QueueThread = std::jthread{ &SDLSoundService::SDLSoundServiceImpl::ProcessQueue, this };
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

			/*int channel = */Mix_FadeInMusic(m_pMusic.at(fullPath), newLoop, fadeInMs);
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
			Mix_Music* newMusic = Mix_LoadMUS(fullPath.c_str());
			assert(newMusic != NULL && L"failed to load music");
			if (newMusic)
			{
				//music was loaded correctly
				m_pMusic.insert(std::make_pair(fullPath, newMusic));
			}
		}
	}

	void ProcessEvent(const std::pair<SDLSoundQueueEvent, std::shared_ptr<EventArgs>>& queueEvent)
	{
		switch (queueEvent.first)
		{
		case pep::SDLSoundService::SDLSoundServiceImpl::SDLSoundQueueEvent::PlayEffect:
		{
			auto args = std::dynamic_pointer_cast<PlayEffectEventArgs>(queueEvent.second);
			if (!PlayedSound(args->GetFile()))
			{
				PlayEffect(args->GetFile(), args->GetVolume());
			}
			break;
		}
		case pep::SDLSoundService::SDLSoundServiceImpl::SDLSoundQueueEvent::PauseEffect:
			PauseEffects();
			break;
		case pep::SDLSoundService::SDLSoundServiceImpl::SDLSoundQueueEvent::ResumeEffect:
			ResumeEffects();
			break;
		case pep::SDLSoundService::SDLSoundServiceImpl::SDLSoundQueueEvent::StopEffect:
			StopEffects();
			break;
		case pep::SDLSoundService::SDLSoundServiceImpl::SDLSoundQueueEvent::PlayMusic:
		{
			auto args = std::dynamic_pointer_cast<PlayMusicEventArgs>(queueEvent.second);
			PlayMusic(args->GetFile(), args->GetLoop(), args->GetVolume(), args->GetFadeInSec());
			break;
		}
		case pep::SDLSoundService::SDLSoundServiceImpl::SDLSoundQueueEvent::PauseMusic:
			PauseMusic();
			break;
		case pep::SDLSoundService::SDLSoundServiceImpl::SDLSoundQueueEvent::ResumeMusic:
			ResumeMusic();
			break;
		case pep::SDLSoundService::SDLSoundServiceImpl::SDLSoundQueueEvent::StopMusic:
		{
			auto args = std::dynamic_pointer_cast<StopMusicEventArgs>(queueEvent.second);
			StopMusic(args->GetFadeOutSec());
			break;
		}
		default:
			break;
		}
	}

	bool PlayedSound(const std::string& file)
	{
		auto it = std::find_if(m_PlayedSounds.begin(), m_PlayedSounds.end(), [&](std::string& soundFile) {return soundFile == file; });
		if (it == m_PlayedSounds.cend())
		{
			m_PlayedSounds.emplace_back(file);
			return false;
		}
		else
		{
			return true;
		}
	}

	void ProcessQueue()
	{
		do 
		{
			m_PlayedSounds.clear();
			while (!m_WorkQueue.empty())
			{
				//process first event and pop it
				ProcessEvent(m_WorkQueue.front());
				m_WorkQueue.pop();
			}
			auto lock = std::unique_lock(m_Mutex);
			//wait for the main thread to tell something is on the queue
			m_ConVar.wait(lock, [this] {return !m_EventQueue.empty() || m_Quit; });
			while (!m_EventQueue.empty())
			{
				//move events from event queue to work queue
				m_WorkQueue.push(m_EventQueue.front());
				m_EventQueue.pop();
			}
			lock.unlock();
		} while (!m_Quit);
	}

	std::map<std::string, Mix_Chunk*> m_pEffects;
	std::map<std::string, Mix_Music*> m_pMusic;

	std::queue<std::pair<SDLSoundQueueEvent, std::shared_ptr<EventArgs>>> m_EventQueue;
	std::queue<std::pair<SDLSoundQueueEvent, std::shared_ptr<EventArgs>>> m_WorkQueue;
	std::vector<std::string> m_PlayedSounds;

	std::mutex m_Mutex;
	std::jthread m_QueueThread;
	std::condition_variable m_ConVar;

	std::string m_Path;

	std::atomic_bool m_Quit;
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
	auto e = std::make_shared <PlayEffectEventArgs>( file, volume );
	m_pImpl->AddToQueue(SDLSoundServiceImpl::SDLSoundQueueEvent::PlayEffect, e);
}

void pep::SDLSoundService::PauseEffects()
{
	m_pImpl->AddToQueue(SDLSoundServiceImpl::SDLSoundQueueEvent::PauseEffect, nullptr);
}

void pep::SDLSoundService::ResumeEffects()
{
	m_pImpl->AddToQueue(SDLSoundServiceImpl::SDLSoundQueueEvent::ResumeEffect, nullptr);
}

void pep::SDLSoundService::StopEffects()
{
	m_pImpl->AddToQueue(SDLSoundServiceImpl::SDLSoundQueueEvent::StopEffect, nullptr);
}

void pep::SDLSoundService::PlayMusic(const std::string& file, bool loop, const int volume, float fadeInSec)
{
	auto e = std::make_shared<PlayMusicEventArgs>(file, loop, volume, fadeInSec);
	m_pImpl->AddToQueue(SDLSoundServiceImpl::SDLSoundQueueEvent::PlayMusic, e);
}

void pep::SDLSoundService::PauseMusic()
{
	m_pImpl->AddToQueue(SDLSoundServiceImpl::SDLSoundQueueEvent::PauseMusic, nullptr);
}

void pep::SDLSoundService::ResumeMusic()
{
	m_pImpl->AddToQueue(SDLSoundServiceImpl::SDLSoundQueueEvent::ResumeMusic, nullptr);
}

void pep::SDLSoundService::StopMusic(float fadeOutSec)
{
	auto e = std::make_shared<StopMusicEventArgs>(fadeOutSec);
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