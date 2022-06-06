#pragma once
#include "BaseComponent.h"
#include "Subject.h"
#include "TextureComponent.h"


class SprayPepperComponent final : public pep::BaseComponent, public pep::Subject
{
public:
	SprayPepperComponent(const std::weak_ptr<pep::Object>& object, pep::TextureComponent* leftVisual, pep::TextureComponent* rightVisual, float width, float height, float cooldown, float stunTime);
	~SprayPepperComponent() = default;
	SprayPepperComponent(const SprayPepperComponent& other) = delete;
	SprayPepperComponent(SprayPepperComponent&& other) = delete;
	SprayPepperComponent& operator=(const SprayPepperComponent& other) = delete;
	SprayPepperComponent& operator=(SprayPepperComponent&& other) = delete;

	void Update() override;
	void Render() const override;

	void SprayRight();
	void SprayLeft();
private:
	pep::TextureComponent* m_pLeftVisual;
	pep::TextureComponent* m_pRightVisual;
	float m_Width;
	float m_Height;
	float m_SprayCooldown;
	float m_SprayTimeAcc;
	float m_StunTime;
	bool m_OnCooldown;
};
