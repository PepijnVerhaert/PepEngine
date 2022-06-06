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
	Gamemode gamemode = Gamemode::Single;

	auto scene = pep::SceneManager::GetInstance().CreateScene("Test");
	pep::SceneManager::GetInstance().SetSceneActive("Test");
	pep::SceneManager::GetInstance().SetSceneVisible("Test");

	auto player1 = CreatePeterPepper(nullptr, 1, true);
	player1->SetLocalTransform(pep::Transform2D{ glm::vec2{100.f, 100.f} });
	scene->Add(player1);

	pep::Object* pPlayer2 = nullptr;
	switch (gamemode)
	{
	case Gamemode::Versus:
		break;
	case Gamemode::Coop:
	{
		auto player2 = CreatePeterPepper(nullptr, 0, false);
		player2->SetLocalTransform(pep::Transform2D{ glm::vec2{100.f, 100.f} });
		scene->Add(player2);
		pPlayer2 = player2.get();
		break;
	}
	default:
		break;
	}

	LoadLevel("../Data/level1.pep", *scene, gamemode, player1.get(), pPlayer2);
}