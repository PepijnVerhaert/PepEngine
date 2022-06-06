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
#include "LevelLoader.h"

void CreateTestScene()
{
	auto scene = pep::SceneManager::GetInstance().CreateScene("Test");
	pep::SceneManager::GetInstance().SetSceneActive("Test");
	pep::SceneManager::GetInstance().SetSceneVisible("Test");

	auto player1 = CreatePeterPepper(nullptr, 0, true);
	player1->SetLocalTransform(pep::Transform2D{ glm::vec2{100.f, 100.f} });
	scene->Add(player1);

	LoadLevel("../Data/level1.pep", *scene, Gamemode::Single, player1.get(), nullptr);
}