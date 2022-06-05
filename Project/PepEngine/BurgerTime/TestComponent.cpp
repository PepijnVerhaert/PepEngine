#include "TestComponent.h"
#include <iostream>
#include "SoundInclude.h"

TestComponent::TestComponent(const std::weak_ptr<pep::Object>& object)
	:pep::BaseComponent(object)
	,m_TimesPressed{0}
{
}

void TestComponent::Update()
{
}

void TestComponent::Render() const
{
}

void TestComponent::Test()
{
	++m_TimesPressed;
	pep::ServiceLocator::GetSoundService()->PlayEffect("FX_ScorePoint.mp3", 100);
	std::cout << "test function in TestComponent called " << m_TimesPressed << " times\n";
}
