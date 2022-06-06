#pragma once
#include <memory>
#include "Object.h"
#include "MovementComponent.h"
#include "TextureComponent.h"
#include "MovementControlComponent.h"

std::shared_ptr<pep::Object> CreateHotdog(LevelLayoutComponent* pLevelLayout, bool forPlayer, pep::Object* pTarget)
{
	auto mrHotdog = std::make_shared<pep::Object>();
	auto mrHotdogMovement = std::make_shared<MovementComponent>(mrHotdog, 100.f, pLevelLayout);
	auto mrHotdogVisual = std::make_shared<pep::TextureComponent>(mrHotdog, "Enemies/Hotdog_Left.png", 24, 32);
	if (!forPlayer)
	{
		auto mrHotdogController = std::make_shared<MovementControlComponent>(mrHotdog, mrHotdogMovement.get(), pTarget);
		mrHotdog->AddComponent(mrHotdogController);
	}
	mrHotdog->AddComponent(mrHotdogMovement);
	mrHotdog->AddComponent(mrHotdogVisual);
	return mrHotdog;
}