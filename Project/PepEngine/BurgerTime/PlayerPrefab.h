#pragma once
#include <memory>
#include "Object.h"
#include "MovementComponent.h"
#include "TextureComponent.h"
#include "SprayPepperComponent.h"
#include "InputManager.h"
#include "MoveUpCommand.h"
#include "MoveDownCommand.h"
#include "MoveLeftCommand.h"
#include "MoveRightCommand.h"
#include "SprayLeftCommand.h"
#include "SprayRightCommand.h"

std::shared_ptr<pep::Object> CreatePeterPepper(LevelLayoutComponent* pLevelLayout, unsigned int controllerNb, bool useKeyboard)
{
	auto peterPepper = std::make_shared<pep::Object>();

	auto rightSpray = std::make_shared<pep::Object>();
	auto leftSpray = std::make_shared<pep::Object>();
	auto rightSprayVisual = std::make_shared<pep::TextureComponent>(rightSpray, "PeterPepper/Spray_Left.png", 24, 32);
	rightSprayVisual->SetVisibility(false);
	auto leftSprayVisual = std::make_shared<pep::TextureComponent>(leftSpray, "PeterPepper/Spray_Left.png", 24, 32);
	leftSprayVisual->SetVisibility(false);
	rightSpray->AddComponent(rightSprayVisual);
	leftSpray->AddComponent(leftSprayVisual);

	rightSpray->SetLocalTransform(pep::Transform2D{ {24.f, 0.f} });
	leftSpray->SetLocalTransform(pep::Transform2D{ {-24.f, 0.f} });
	
	rightSpray->SetParent(rightSpray, peterPepper, false);
	leftSpray->SetParent(leftSpray, peterPepper, false);

	auto peterMovement = std::make_shared<MovementComponent>(peterPepper, 200.f, pLevelLayout);
	auto peterVisual = std::make_shared<pep::TextureComponent>(peterPepper, "PeterPepper/PP_Left.png", 24, 32);
	auto sprayPepper = std::make_shared<SprayPepperComponent>(peterPepper, leftSprayVisual.get(), rightSprayVisual.get(), 24.f, 32.f, 0.5f, 1.5f);
	peterPepper->AddComponent(peterMovement);
	peterPepper->AddComponent(peterVisual);
	peterPepper->AddComponent(sprayPepper);



	pep::InputManager::GetInstance().AddControllerCommand(pep::ControllerButton::DPad_Up, pep::ButtonState::Down, std::make_shared<MoveUpCommand>(peterPepper.get(), peterMovement.get()), controllerNb);
	pep::InputManager::GetInstance().AddControllerCommand(pep::ControllerButton::DPad_Down, pep::ButtonState::Down, std::make_shared<MoveDownCommand>(peterPepper.get(), peterMovement.get()), controllerNb);
	pep::InputManager::GetInstance().AddControllerCommand(pep::ControllerButton::DPad_Left, pep::ButtonState::Down, std::make_shared<MoveLeftCommand>(peterPepper.get(), peterMovement.get()), controllerNb);
	pep::InputManager::GetInstance().AddControllerCommand(pep::ControllerButton::DPad_Right, pep::ButtonState::Down, std::make_shared<MoveRightCommand>(peterPepper.get(), peterMovement.get()), controllerNb);

	pep::InputManager::GetInstance().AddControllerCommand(pep::ControllerButton::Button_West, pep::ButtonState::PressedThisFrame, std::make_shared<SprayLeftCommand>(peterPepper.get()), controllerNb);
	pep::InputManager::GetInstance().AddControllerCommand(pep::ControllerButton::Button_East, pep::ButtonState::PressedThisFrame, std::make_shared<SprayRightCommand>(peterPepper.get()), controllerNb);

	if (useKeyboard)
	{
		pep::InputManager::GetInstance().AddKeyboardCommand(pep::KeyboardKey::p_W, pep::ButtonState::Down, std::make_shared<MoveUpCommand>(peterPepper.get(), peterMovement.get()));
		pep::InputManager::GetInstance().AddKeyboardCommand(pep::KeyboardKey::p_S, pep::ButtonState::Down, std::make_shared<MoveDownCommand>(peterPepper.get(), peterMovement.get()));
		pep::InputManager::GetInstance().AddKeyboardCommand(pep::KeyboardKey::p_A, pep::ButtonState::Down, std::make_shared<MoveLeftCommand>(peterPepper.get(), peterMovement.get()));
		pep::InputManager::GetInstance().AddKeyboardCommand(pep::KeyboardKey::p_D, pep::ButtonState::Down, std::make_shared<MoveRightCommand>(peterPepper.get(), peterMovement.get()));

		pep::InputManager::GetInstance().AddKeyboardCommand(pep::KeyboardKey::p_LEFT, pep::ButtonState::PressedThisFrame, std::make_shared<SprayLeftCommand>(peterPepper.get()));
		pep::InputManager::GetInstance().AddKeyboardCommand(pep::KeyboardKey::p_RIGHT, pep::ButtonState::PressedThisFrame, std::make_shared<SprayRightCommand>(peterPepper.get()));
	}

	return peterPepper;
}