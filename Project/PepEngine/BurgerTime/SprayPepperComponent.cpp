#include "SprayPepperComponent.h"
#include "GameTime.h"
#include "StunEvent.h"
#include "Object.h"

SprayPepperComponent::SprayPepperComponent(const std::weak_ptr<pep::Object>& object, pep::TextureComponent* leftVisual, pep::TextureComponent* rightVisual, float width, float height, float cooldown, float stunTime)
	:BaseComponent(object)
	,Subject()
	,m_pLeftVisual{leftVisual}
	,m_pRightVisual{rightVisual}
	,m_Width{width}
	,m_Height{height}
	,m_SprayCooldown{cooldown}
	,m_SprayTimeAcc{0.f}
	,m_StunTime{stunTime}
	,m_OnCooldown{false}
{
}

void SprayPepperComponent::Update()
{
	if (m_SprayTimeAcc < m_SprayCooldown)
	{
		m_SprayTimeAcc += pep::GameTime::GetInstance().GetDeltaTime();
	}
	if (m_OnCooldown && m_SprayTimeAcc >= m_SprayCooldown)
	{
		m_pLeftVisual->SetVisibility(false);
		m_pRightVisual->SetVisibility(false);
		m_OnCooldown = false;
	}
}

void SprayPepperComponent::Render() const
{
}

void SprayPepperComponent::SprayRight()
{
	glm::vec2 pos = m_pObject.lock()->GetWorldTransform().GetPosition();
	auto pE = std::make_shared<StunEvent>(m_StunTime, pos.x + m_Width, pos.y, m_Width, m_Height);
	Notify(pE);
	m_OnCooldown = true;
	m_SprayTimeAcc = 0.f;
	m_pRightVisual->SetVisibility(true);
}

void SprayPepperComponent::SprayLeft()
{
	glm::vec2 pos = m_pObject.lock()->GetWorldTransform().GetPosition();
	auto pE = std::make_shared<StunEvent>(m_StunTime, pos.x - m_Width, pos.y, m_Width, m_Height);
	Notify(pE);
	m_OnCooldown = true;
	m_SprayTimeAcc = 0.f;
	m_pLeftVisual->SetVisibility(true);
}
