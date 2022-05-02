#include "TestComponent.h"
#include <iostream>

TestComponent::TestComponent(const std::weak_ptr<pep::Object>& object)
	:pep::BaseComponent(object)
	,m_TimesPressed{0}
{
}

void TestComponent::Update()
{
}

void TestComponent::Test()
{
	++m_TimesPressed;
	std::cout << "test function in TestComponent called " << m_TimesPressed << " times\n";
}
