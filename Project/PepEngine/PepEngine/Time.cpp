#include "PepEnginePCH.h"
#include "Time.h"

using namespace pep;

float Time::GetDeltaTime() const
{
    return m_DeltaTime;
}

void Time::SetDeltaTime(float deltaTime)
{
    m_DeltaTime = deltaTime;
}

float Time::GetStartTime() const
{
    return m_StartTime;
}

void Time::SetStartTime(float startTime)
{
    m_StartTime = startTime;
}
