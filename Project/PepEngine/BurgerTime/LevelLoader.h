#pragma once
#include <string>
#include <vector>
#include "BinaryReader.h"
#include "Scene.h"
#include "Helper.h"
#include "LevelLayoutComponent.h"
#include "Object.h"
#include "PlayerPrefab.h"
#include "EnemyPrefab.h"
#include "EnemyHitboxComponent.h"


void LoadLevel(const std::string& file, pep::Scene& scene, Gamemode gamemode, pep::Object* pPlayer1, pep::Object* pPlayer2)
{
	size_t bytesPerTile = 2;
	size_t gridWidth = 17;
	size_t gridHeight = 12;
	glm::vec2 tileSize{ 24.f, 32.f };
	glm::vec2 gridOffset{ 100.f, 50.f };

	auto pLevel = std::make_shared<pep::Object>();
	auto layoutComponent = std::make_shared<LevelLayoutComponent>(pLevel, gridWidth, gridHeight, tileSize, gridOffset);
	pLevel->AddComponent(layoutComponent);
	scene.Add(pLevel);

	if(pPlayer1)
		pPlayer1->GetComponent<MovementComponent>()->SetLevelLayoutComponent(layoutComponent.get());
	if(pPlayer2)
		pPlayer2->GetComponent<MovementComponent>()->SetLevelLayoutComponent(layoutComponent.get());

	std::vector<char> levelData{};
	if (!pep::BinaryToChar(file, levelData))
	{
		return;
	}
	if (levelData.size() / bytesPerTile != gridWidth * gridHeight)
	{
		return;
	}

	for (size_t i = 0; i < levelData.size()-1; i+= bytesPerTile)
	{
		char levelByte = levelData[i];
		char burgerByte = levelData[i+1];
		if (levelByte != static_cast<char>(LevelByte::empty))
		{
			glm::vec2 pos{};
			layoutComponent->GetTilePos(pos, i / bytesPerTile);
			if (levelByte & static_cast<char>(LevelByte::ladder))
			{
				//add walkable (i+1)/bytesPerTile
				layoutComponent->AddWalkable((i + 1) / bytesPerTile);
				auto pLadderVisual = std::make_shared<pep::Object>();
				auto pVisualComponent = std::make_shared<pep::TextureComponent>(pLadderVisual, "Level/Ladder.png", static_cast<int>(tileSize.x), static_cast<int>(tileSize.y));

				pLadderVisual->AddComponent(pVisualComponent);
				pLadderVisual->SetLocalTransform({ pos });

				pLadderVisual->SetParent(pLadderVisual, pLevel, true);
			}
			if (levelByte & static_cast<char>(LevelByte::platform))
			{
				//add walkable (i+1)/bytesPerTile
				layoutComponent->AddWalkable((i + 1) / bytesPerTile);
				auto pPlatformVisual = std::make_shared<pep::Object>();
				auto pVisualComponent = std::make_shared<pep::TextureComponent>(pPlatformVisual, "Level/Platform.png", static_cast<int>(tileSize.x), static_cast<int>(tileSize.y));

				pPlatformVisual->AddComponent(pVisualComponent);
				pPlatformVisual->SetLocalTransform({ pos });

				pPlatformVisual->SetParent(pPlatformVisual, pLevel, true);
			}
			if (levelByte & static_cast<char>(LevelByte::hotdog))
			{
				switch (gamemode)
				{
				case Gamemode::Single:
				{
					auto pHotdog = CreateHotdog(layoutComponent.get(), false, pPlayer1);
					auto pHotdogHitbox = std::make_shared<EnemyHitboxComponent>(pHotdog, 24.f, 32.f, pHotdog->GetComponent<MovementComponent>().get());
					pHotdog->AddComponent(pHotdogHitbox);
					if (pPlayer1)
						pPlayer1->GetComponent<SprayPepperComponent>()->AddObserver(pHotdogHitbox);
					if (pPlayer2)
						pPlayer2->GetComponent<SprayPepperComponent>()->AddObserver(pHotdogHitbox);
					pHotdog->SetLocalTransform({ pos });
					scene.Add(pHotdog);
					break;
				}
				case Gamemode::Coop:
				{
					pep::Object* pHotdogTarget = pPlayer1;
					if ((i / 2) % 2)
					{
						pHotdogTarget = pPlayer2;
					}
					auto pHotdog = CreateHotdog(layoutComponent.get(), false, pPlayer1);
					auto pHotdogHitbox = std::make_shared<EnemyHitboxComponent>(pHotdog, 24.f, 32.f, pHotdog->GetComponent<MovementComponent>().get());
					pHotdog->AddComponent(pHotdogHitbox);
					if (pPlayer1)
						pPlayer1->GetComponent<SprayPepperComponent>()->AddObserver(pHotdogHitbox);
					if (pPlayer2)
						pPlayer2->GetComponent<SprayPepperComponent>()->AddObserver(pHotdogHitbox);
					pHotdog->SetLocalTransform({ pos });
					scene.Add(pHotdog);
					break;
				}
				default:
					break;
				}
			}
			if (levelByte & static_cast<char>(LevelByte::pickle))
			{

			}
			if (levelByte & static_cast<char>(LevelByte::egg))
			{
				switch (gamemode)
				{
				case Gamemode::Versus:
					pPlayer2->SetLocalTransform(pep::Transform2D{ pos });
					break;
				case Gamemode::Single:
				case Gamemode::Coop:
					break;
				default:
					break;
				}
			}
			if (levelByte & static_cast<char>(LevelByte::pepper))
			{
				pPlayer1->SetLocalTransform(pep::Transform2D{ pos });
			}
			if (levelByte & static_cast<char>(LevelByte::salt))
			{
				switch (gamemode)
				{
				case Gamemode::Coop:
					pPlayer2->SetLocalTransform(pep::Transform2D{ pos });
					break;
				default:
					break;
				}
			}
		}

		if (burgerByte != static_cast<char>(BurgerByte::empty))
		{
			if (burgerByte & static_cast<char>(BurgerByte::bunTop))
			{

			}
			if (burgerByte & static_cast<char>(BurgerByte::bunBottom))
			{

			}
			if (burgerByte & static_cast<char>(BurgerByte::meat))
			{

			}
			if (burgerByte & static_cast<char>(BurgerByte::cheese))
			{

			}
			if (burgerByte & static_cast<char>(BurgerByte::lettuce))
			{

			}
			if (burgerByte & static_cast<char>(BurgerByte::tomato))
			{

			}
			if (burgerByte & static_cast<char>(BurgerByte::plate))
			{

			}
		}
	}
}