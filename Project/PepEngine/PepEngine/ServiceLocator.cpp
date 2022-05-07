#include "PepEnginePCH.h"
#include "ServiceLocator.h"
#include "BaseSoundService.h"

using namespace pep;

//sound service
NullSoundService ServiceLocator::m_NullSoundService;
BaseSoundService* ServiceLocator::m_pSoundService = &m_NullSoundService;

BaseSoundService* pep::ServiceLocator::GetSoundService()
{
	return m_pSoundService;
}

void pep::ServiceLocator::SetSoundService(BaseSoundService* pSoundService)
{
	if (pSoundService)
	{
		m_pSoundService = pSoundService;
	}
	else
	{
		m_pSoundService = &m_NullSoundService;
	}
}
