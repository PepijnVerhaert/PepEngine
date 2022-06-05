#pragma once
#include "SceneManager.h"
#include "Scene.h"
#include "Object.h"
#include "InputManager.h"

#include "TestComponent.h"
#include "TestCommand.h"

void CreateTestScene()
{
	auto scene = pep::SceneManager::GetInstance().CreateScene("Test");
	auto testObject = std::make_shared<pep::Object>();
	testObject->AddComponent(std::make_shared<TestComponent>(testObject));
	scene->Add(testObject);

	pep::InputManager::GetInstance().AddControllerCommand(pep::ControllerButton::Button_South, pep::ButtonState::PressedThisFrame, std::make_shared<TestCommand>(testObject.get()), 0);
	pep::InputManager::GetInstance().AddKeyboardCommand(pep::KeyboardKey::p_Y, pep::ButtonState::PressedThisFrame, std::make_shared<TestCommand>(testObject.get()));
}