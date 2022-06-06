#pragma once
#include "SceneManager.h"
#include "Scene.h"
#include "Object.h"
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



	std::shared_ptr<pep::Object> pPlayer1{};
	std::shared_ptr<pep::Object> pPlayer2{};
	switch (gamemode)
	{
	case Gamemode::Single:
	{
		pPlayer1 = CreatePeterPepper(nullptr, 0, true);
		scene->Add(pPlayer1);
		break;
	}
	case Gamemode::Versus:
	{
		pPlayer1 = CreatePeterPepper(nullptr, 1, true);
		scene->Add(pPlayer1);

		pPlayer2 = CreateHotdogPlayer(nullptr, 0, false);
		scene->Add(pPlayer2);
		break;
	}
	case Gamemode::Coop:
	{
		pPlayer1 = CreatePeterPepper(nullptr, 1, true);
		scene->Add(pPlayer1);

		pPlayer2 = CreatePeterPepper(nullptr, 0, false);
		scene->Add(pPlayer2);
		break;
	}
	default:
		break;
	}

	LoadLevel("../Data/level1.pep", *scene, gamemode, pPlayer1, pPlayer2);
}