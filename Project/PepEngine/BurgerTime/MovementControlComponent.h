#pragma once
#include "BaseComponent.h" 

class MovementComponent;
class MovementControlComponent final : public pep::BaseComponent
{
public:
	MovementControlComponent(const std::weak_ptr<pep::Object>& object, MovementComponent* pMovement, pep::Object* pTarget);
	~MovementControlComponent() = default;
	MovementControlComponent(const MovementControlComponent& other) = delete;
	MovementControlComponent(MovementControlComponent&& other) = delete;
	MovementControlComponent& operator=(const MovementControlComponent& other) = delete;
	MovementControlComponent& operator=(MovementControlComponent&& other) = delete;

	void Update() override;
	void Render() const override;

private:
	MovementComponent* m_pMovement;
	pep::Object* m_pTarget;
};
