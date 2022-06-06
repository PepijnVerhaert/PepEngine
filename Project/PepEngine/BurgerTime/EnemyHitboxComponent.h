#pragma once
#include "BaseComponent.h"
#include "Observer.h"

class MovementComponent;
class EnemyHitboxComponent final : public pep::BaseComponent, public pep::Observer
{
public:
	EnemyHitboxComponent(const std::weak_ptr<pep::Object>& object, float width, float height, MovementComponent* pMovement);
	~EnemyHitboxComponent() = default;
	EnemyHitboxComponent(const EnemyHitboxComponent& other) = delete;
	EnemyHitboxComponent(EnemyHitboxComponent&& other) = delete;
	EnemyHitboxComponent& operator=(const EnemyHitboxComponent& other) = delete;
	EnemyHitboxComponent& operator=(EnemyHitboxComponent&& other) = delete;

	void Update() override;
	void Render() const override;

	void Notify(const std::shared_ptr<pep::BaseObserverEvent>& pEvent) override;
private:
	MovementComponent* m_pMovement;
	float m_Width;
	float m_Height;
	float m_StunTimeAcc;
	float m_StunDuration;
	bool m_Stunned;
};
