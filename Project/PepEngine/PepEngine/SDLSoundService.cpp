#include "PepEnginePCH.h"
#include "SDLSoundService.h"

using namespace pep;

pep::SDLSoundService::SDLSoundService()
{
}

pep::SDLSoundService::~SDLSoundService()
{
	auto wave = Mix_LoadWAV("");
	Mix_CloseAudio();
}

int pep::SDLSoundService::Play(const int id, const int volume)
{
	return 0;
}

void pep::SDLSoundService::Pause(const int id, const int channel)
{
}

void pep::SDLSoundService::Stop(const int id, const int channel)
{
}

void pep::SDLSoundService::ProcessSound()
{
}

int pep::SDLSoundService::Load(const std::string& file)
{
	if (m_LoadedEffects.find(file) == m_LoadedEffects.end())
	{
		//file is a new sound effect
		auto effect = Mix_LoadWAV(file.c_str());
		if (effect)
		{
			//effect was loaded correctly
			m_Effects.push_back(effect);
			m_LoadedEffects.insert(std::make_pair(file, m_Effects.size()-1));
			return int(m_Effects.size() - 1);
		}
	}
	else
	{
		//file has already been loaded
		return int(m_LoadedEffects.at(file));
	}
	//something went wrong
	return -1;
}

void pep::SDLSoundService::Initialize()
{
	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096);

}
