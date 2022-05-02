#pragma once
#include "Singleton.h"

namespace pep
{
	class GameTime final : public Singleton<GameTime>
	{
	public:
		float GetDeltaTime() const;
		void SetDeltaTime(float deltaTime);
		float GetStartTime() const;
		void SetStartTime(float startTime);
	private:
		friend class Singleton<GameTime>;
		GameTime() = default;
		float m_DeltaTime;
		float m_StartTime;
	};
}