#pragma once
#include <BaseComponent.h>

class LevelLayoutComponent;
class MovementComponent final : public pep::BaseComponent
{
public:
	MovementComponent(const std::weak_ptr<pep::Object>& object, float speed, LevelLayoutComponent* pLevelLayout);
	~MovementComponent() = default;
	MovementComponent(const MovementComponent& other) = delete;
	MovementComponent(MovementComponent&& other) = delete;
	MovementComponent& operator=(const MovementComponent& other) = delete;
	MovementComponent& operator=(MovementComponent&& other) = delete;

	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();

	void Update() override;
	void Render() const override;

	void Disable();
	void Enable();

	void SetLevelLayoutComponent(LevelLayoutComponent* layout);
private:
	float m_X;
	float m_Y;
	float m_Speed;
	bool m_CanMove;
	LevelLayoutComponent* m_pLevelLayout;
};
