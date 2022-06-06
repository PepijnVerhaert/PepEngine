#pragma once
#include "NullSoundService.h"
#include "NullInputService.h"

namespace pep
{
	class BaseSoundService;
	class BaseInputService;
	class ServiceLocator final
	{
	public:
		static BaseSoundService* GetSoundService();
		static void SetSoundService(BaseSoundService* pSoundService);
		static BaseInputService* GetInputService();
		static void SetInputService(BaseInputService* pInputService);
	private:
		static BaseSoundService* m_pSoundService;
		static NullSoundService m_NullSoundService;
		static BaseInputService* m_pInputService;
		static NullInputService m_NullInputService;
	};
}