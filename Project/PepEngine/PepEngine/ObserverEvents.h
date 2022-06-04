#pragma once
#include "BaseObserverEvent.h"

namespace pep
{
	class Object;
	struct DeleteSubject : public BaseObserverEvent
	{
		DeleteSubject(Object* pSubject)
			:BaseObserverEvent()
			,pSubject{pSubject}
		{}
		Object* pSubject;
	};
}