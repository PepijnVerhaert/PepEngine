#pragma once
#include "BaseComponent.h"

class TestComponent final : public pep::BaseComponent
{
public:
	TestComponent(const std::weak_ptr<pep::Object>& object);
	~TestComponent() = default;
	TestComponent(const TestComponent & other) = delete;
	TestComponent(TestComponent && other) = delete;
	TestComponent& operator=(const TestComponent & other) = delete;
	TestComponent& operator=(TestComponent && other) = delete;

	void Update() override;
	void Render() const override;
	void Test();
private:
	int m_TimesPressed;
};

