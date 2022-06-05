#pragma once
#include <memory>
#include "Object.h"
#include "MovementComponent.h"

const std::shared_ptr<pep::Object>& CreatePeterPepper()
{
	auto peterPepper = std::make_shared<pep::Object>();
	auto peterMovement = std::make_shared<MovementComponent>(peterPepper);
	auto peterVisual = std::make_shared<>
	peterPepper->AddComponent(peterMovement);
	return peterPepper;
}