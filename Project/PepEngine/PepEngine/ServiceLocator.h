#pragma once
#include "NullSoundService.h"

namespace pep
{
	class BaseSoundService;
	class ServiceLocator final
	{
	public:
		static BaseSoundService* GetSoundService();
		static void SetSoundService(BaseSoundService* pSoundService);
	private:
		static BaseSoundService* m_pSoundService;
		static NullSoundService m_NullSoundService;
	};
}