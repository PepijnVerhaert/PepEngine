#include "PepEnginePCH.h"
#include "ServiceLocator.h"
#include "BaseSoundService.h"
#include "BaseInputService.h"

using namespace pep;

//sound service
NullSoundService ServiceLocator::m_NullSoundService;
BaseSoundService* ServiceLocator::m_pSoundService = &m_NullSoundService;

//input service
NullInputService ServiceLocator::m_NullInputService;
BaseInputService* ServiceLocator::m_pInputService = &m_NullInputService;

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

BaseInputService* pep::ServiceLocator::GetInputService()
{
	return m_pInputService;
}

void pep::ServiceLocator::SetInputService(BaseInputService* pInputService)
{
	if (pInputService)
	{
		m_pInputService = pInputService;
	}
	else
	{
		m_pInputService = &m_NullInputService;
	}
}