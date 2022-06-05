#pragma once
#include <memory>
#include "Object.h"
#include "MovementComponent.h"
#include "TextureComponent.h"
#include "InputManager.h"
#include "MoveUpCommand.h"
#include "MoveDownCommand.h"
#include "MoveLeftCommand.h"
#include "MoveRightCommand.h"

std::shared_ptr<pep::Object> CreatePeterPepper(LevelLayoutComponent* pLevelLayout, unsigned int controllerNb, bool useKeyboard)
{
	auto peterPepper = std::make_shared<pep::Object>();
	auto peterMovement = std::make_shared<MovementComponent>(peterPepper, 100.f, pLevelLayout);
	auto peterVisual = std::make_shared<pep::TextureComponent>(peterPepper, "PeterPepper/PP_Left.png");
	peterPepper->AddComponent(peterMovement);
	peterPepper->AddComponent(peterVisual);

	pep::InputManager::GetInstance().AddControllerCommand(pep::ControllerButton::DPad_Up, pep::ButtonState::Down, std::make_shared<MoveUpCommand>(peterPepper.get(), peterMovement.get()), controllerNb);
	pep::InputManager::GetInstance().AddControllerCommand(pep::ControllerButton::DPad_Down, pep::ButtonState::Down, std::make_shared<MoveDownCommand>(peterPepper.get(), peterMovement.get()), controllerNb);
	pep::InputManager::GetInstance().AddControllerCommand(pep::ControllerButton::DPad_Left, pep::ButtonState::Down, std::make_shared<MoveLeftCommand>(peterPepper.get(), peterMovement.get()), controllerNb);
	pep::InputManager::GetInstance().AddControllerCommand(pep::ControllerButton::DPad_Right, pep::ButtonState::Down, std::make_shared<MoveRightCommand>(peterPepper.get(), peterMovement.get()), controllerNb);

	if (useKeyboard)
	{
		pep::InputManager::GetInstance().AddKeyboardCommand(pep::KeyboardKey::p_W, pep::ButtonState::Down, std::make_shared<MoveUpCommand>(peterPepper.get(), peterMovement.get()));
		pep::InputManager::GetInstance().AddKeyboardCommand(pep::KeyboardKey::p_S, pep::ButtonState::Down, std::make_shared<MoveDownCommand>(peterPepper.get(), peterMovement.get()));
		pep::InputManager::GetInstance().AddKeyboardCommand(pep::KeyboardKey::p_A, pep::ButtonState::Down, std::make_shared<MoveLeftCommand>(peterPepper.get(), peterMovement.get()));
		pep::InputManager::GetInstance().AddKeyboardCommand(pep::KeyboardKey::p_D, pep::ButtonState::Down, std::make_shared<MoveRightCommand>(peterPepper.get(), peterMovement.get()));
	}

	return peterPepper;
}