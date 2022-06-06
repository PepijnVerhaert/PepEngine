#pragma once
#include "BaseObserverEvent.h"

class Object;
struct StunEvent : public pep::BaseObserverEvent
{
	StunEvent(float stunTime, float x, float y, float width, float height)
		:BaseObserverEvent()
		, stunTime{ stunTime }
		, x{ x }
		, y{ y }
		, w{ width }
		, h{ height }
	{}
	float stunTime, x, y, w, h;
};
