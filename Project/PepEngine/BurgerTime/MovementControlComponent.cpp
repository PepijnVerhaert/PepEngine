#include "MovementControlComponent.h"
#include "MovementComponent.h"
#include "Object.h"

MovementControlComponent::MovementControlComponent(const std::weak_ptr<pep::Object>& object, MovementComponent* pMovement, pep::Object* pTarget)
	:pep::BaseComponent(object)
	, m_pMovement{ pMovement }
	, m_pTarget{ pTarget }
{
}

void MovementControlComponent::Update()
{
	glm::vec2 ownPos = m_pObject.lock()->GetWorldTransform().GetPosition();
	glm::vec2 targetPos = m_pTarget->GetWorldTransform().GetPosition();

	glm::vec2 distanceToTarget = targetPos - ownPos;

	if (distanceToTarget.y > 0.f)
	{
		m_pMovement->MoveUp();
	}
	else
	{
		m_pMovement->MoveDown();
	}
	if (abs(distanceToTarget.y) * 1.5f < abs(distanceToTarget.x))
	{
		if (distanceToTarget.x > 0.f)
		{
			m_pMovement->MoveRight();
		}
		else
		{
			m_pMovement->MoveLeft();
		}
	}
}

void MovementControlComponent::Render() const
{
}
