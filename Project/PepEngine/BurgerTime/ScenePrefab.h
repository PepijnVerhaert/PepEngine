#pragma once
#include "SceneManager.h"
#include "Scene.h"
#include "Object.h"
#include "InputManager.h"
#include <memory>

#include "TestComponent.h"
#include "TestCommand.h"
#include "PlayerPrefab.h"
#include "LevelLayoutComponent.h"

void CreateTestScene()
{
	auto scene = pep::SceneManager::GetInstance().CreateScene("Test");
	pep::SceneManager::GetInstance().SetSceneActive("Test");
	pep::SceneManager::GetInstance().SetSceneVisible("Test");
	auto testObject = std::make_shared<pep::Object>();
	auto layoutComponent = std::make_shared<LevelLayoutComponent>(testObject, static_cast<size_t>(17), static_cast<size_t>(12), glm::vec2{ 24.f, 32.f }, glm::vec2{});
	testObject->AddComponent(layoutComponent);
	scene->Add(testObject);

	auto player1 = CreatePeterPepper(layoutComponent.get(), 0, true);
	player1->SetLocalTransform(pep::Transform2D{ glm::vec2{100.f, 100.f} });
	scene->Add(player1);
}