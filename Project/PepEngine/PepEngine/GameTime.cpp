#include "PepEnginePCH.h"
#include "GameTime.h"

using namespace pep;

float GameTime::GetDeltaTime() const
{
    return m_DeltaTime;
}

void GameTime::SetDeltaTime(float deltaTime)
{
    m_DeltaTime = deltaTime;
}

float GameTime::GetStartTime() const
{
    return m_StartTime;
}

void GameTime::SetStartTime(float startTime)
{
    m_StartTime = startTime;
}
