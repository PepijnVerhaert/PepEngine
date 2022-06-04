#pragma once
#include <memory>

namespace pep
{
	struct BaseObserverEvent;
	class Observer
	{
	public:
		Observer() = default;
		virtual ~Observer() = default;
		virtual void Notify(const std::shared_ptr<BaseObserverEvent>& pEvent) = 0;
	};
}