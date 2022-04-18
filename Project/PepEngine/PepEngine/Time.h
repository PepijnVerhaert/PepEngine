#pragma once
#include "Singleton.h"

namespace pep
{
	class Time final : public Singleton<Time>
	{
	public:
		float GetDeltaTime() const;
		void SetDeltaTime(float deltaTime);
		float GetStartTime() const;
		void SetStartTime(float startTime);
	private:
		friend class Singleton<Time>;
		Time() = default;
		float m_DeltaTime;
		float m_StartTime;
	};
}