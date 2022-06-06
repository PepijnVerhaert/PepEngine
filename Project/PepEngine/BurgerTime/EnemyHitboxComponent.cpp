#include "EnemyHitboxComponent.h"
#include <iostream>
#pragma warning(push)
#pragma warning(disable: 26495)
#pragma warning(disable: 4201)
#include <glm/glm.hpp>
#pragma warning (pop)
#include <memory>

#include "SoundInclude.h"
#include "MovementComponent.h"
#include "GameTime.h"
#include "StunEvent.h"
#include "Object.h"

EnemyHitboxComponent::EnemyHitboxComponent(const std::weak_ptr<pep::Object>& object, float width, float height, MovementComponent* pMovement)
	:pep::BaseComponent(object)
	, m_Width{ width }
	, m_Height{ height }
	,m_StunDuration{}
	,m_StunTimeAcc{}
	,m_Stunned{false}
	,m_pMovement{pMovement}
{
}

void EnemyHitboxComponent::Update()
{
	if (m_StunTimeAcc < m_StunDuration)
	{
		m_StunTimeAcc += pep::GameTime::GetInstance().GetDeltaTime();
	}
	if (m_Stunned && m_StunTimeAcc >= m_StunDuration)
	{
		m_pMovement->Enable();
		m_Stunned = false;
	}
}

void EnemyHitboxComponent::Render() const
{
}

void EnemyHitboxComponent::Notify(const std::shared_ptr<pep::BaseObserverEvent>& pEvent)
{
	if (typeid(*pEvent.get()) == typeid(StunEvent))
	{
		auto pStunEvent = std::dynamic_pointer_cast<StunEvent>(pEvent);

		glm::vec2 topRightSpray{ pStunEvent->x + pStunEvent->w, pStunEvent->y };
		glm::vec2 bottomLeftSpray{ pStunEvent->x, pStunEvent->y + pStunEvent->h };

		auto pObjectPos = m_pObject.lock()->GetWorldTransform().GetPosition();
		glm::vec2 topRightEnemy{ pObjectPos.x + m_Width, pObjectPos.y };
		glm::vec2 bottomLeftEnemy{ pObjectPos.x, pObjectPos.y + m_Height };

		if (!(
			(topRightSpray.x <= bottomLeftEnemy.x) ||
			(bottomLeftSpray.x >= topRightEnemy.x) ||
			(topRightSpray.y >= bottomLeftEnemy.y) ||
			(bottomLeftSpray.y <= topRightEnemy.y)
			))
		{
			m_StunDuration = pStunEvent->stunTime;
			m_StunTimeAcc = 0.f;
			m_Stunned = true;
			m_pMovement->Disable();
		}
	}
}
