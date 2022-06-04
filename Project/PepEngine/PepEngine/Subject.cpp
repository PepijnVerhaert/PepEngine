#include "PepEnginePCH.h"
#include "Subject.h"
#include "Observer.h"

void pep::Subject::AddObserver(const std::shared_ptr<Observer>& pObserver)
{
	if (std::find_if(m_pObservers.begin(), m_pObservers.end(), [&](std::weak_ptr<Observer>& pO) {return pO.lock() == pObserver; }) == m_pObservers.end())
	{
		m_pObservers.emplace_back(pObserver);
	}
}

void pep::Subject::RemoveObserver(const std::shared_ptr<Observer>& pObserver)
{
	auto it = std::find_if(m_pObservers.begin(), m_pObservers.end(), [&](std::weak_ptr<Observer>& pO) {return pO.lock() == pObserver; });
	m_pObservers.erase(it);
}

void pep::Subject::Notify(const std::shared_ptr<BaseObserverEvent>& pEvent)
{
	for (auto& pObserver : m_pObservers)
	{
		if (std::shared_ptr<Observer> pO = pObserver.lock())
		{
			pO->Notify(pEvent);
		}
	}
}