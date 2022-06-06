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
	float epsilon = 1.f;

	glm::vec2 ownPos = m_pObject.lock()->GetWorldTransform().GetPosition();
	glm::vec2 targetPos = m_pTarget->GetWorldTransform().GetPosition();

	glm::vec2 distanceToTarget = targetPos - ownPos;

	if (abs(distanceToTarget.y) > epsilon)
	{
		if (distanceToTarget.y > 0.f)
		{
			m_pMovement->MoveDown();
		}
		else
		{
			m_pMovement->MoveUp();
		}
	}

	if (abs(distanceToTarget.x) > epsilon)
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
