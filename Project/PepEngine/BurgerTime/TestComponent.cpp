#include "TestComponent.h"
#include <iostream>
#include "SoundInclude.h"
#include "MovementComponent.h"

TestComponent::TestComponent(const std::weak_ptr<pep::Object>& object, MovementComponent* pMove)
	:pep::BaseComponent(object)
	,m_TimesPressed{0}
	,m_pMove{pMove}
{
}

void TestComponent::Update()
{
	m_pMove->MoveUp();
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
