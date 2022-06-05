#include "MovementComponent.h"
#include "Object.h"
#include "LevelLayoutComponent.h"

MovementComponent::MovementComponent(const std::weak_ptr<pep::Object>& object, float speed, LevelLayoutComponent* pLevelLayout)
	:pep::BaseComponent(object)
	, m_X{}
	, m_Y{}
	, m_CanMove{ true }
	, m_Speed{ speed }
	, m_pLevelLayout{ pLevelLayout }
{
}

void MovementComponent::MoveUp()
{
	m_Y -= 1.f;
}

void MovementComponent::MoveDown()
{
	m_Y += 1.f;
}

void MovementComponent::MoveLeft()
{
	m_X -= 1.f;
}

void MovementComponent::MoveRight()
{
	m_X += 1.f;
}

void MovementComponent::Update()
{
	if (m_CanMove)
	{
		auto transform = m_pObject.lock()->GetLocalTransform();
		auto pos = transform.GetPosition();
		Direction dir{Direction::None};
		if (m_X > 0.5f)
			dir = Direction::right;
		else if (m_X < -0.5f)
			dir = Direction::left;
		else if (m_Y > 0.5f)
			dir = Direction::down;
		else if (m_Y < -0.5f)
			dir = Direction::Up;

		m_pLevelLayout->MoveDistanceInDirection(dir, m_Speed, pos);

		transform.SetPosition(pos);
	}
	m_X = 0.f;
	m_Y = 0.f;
}

void MovementComponent::Disable()
{
	m_CanMove = false;
}

void MovementComponent::Enable()
{
	m_CanMove = true;
}
