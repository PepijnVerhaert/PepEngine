#pragma once
#include <string>
#include <vector>
#include "BinaryReader.h"
#include "Scene.h"
#include "Helper.h"


void LoadLevel(const std::string& file, pep::Scene& scene, Gamemode gamemode)
{
	std::vector<char> levelData{};
	if (!pep::BinaryToChar(file, levelData))
	{
		return;
	}
	if (levelData.size() % 2 != 0)
	{
		return;
	}

	for (size_t i = 0; i < levelData.size()-1; i+=2)
	{
		char levelByte = levelData[i];
		char burgerByte = levelData[i+1];
		if (levelByte != static_cast<char>(LevelByte::empty))
		{
			if (levelByte & static_cast<char>(LevelByte::platform))
			{
				//add walkable (i+1)/2

			}
			if (levelByte & static_cast<char>(LevelByte::ladder))
			{
				//add walkable (i+1)/2

			}
			if (levelByte & static_cast<char>(LevelByte::hotdog))
			{

			}
			if (levelByte & static_cast<char>(LevelByte::pickle))
			{

			}
			if (levelByte & static_cast<char>(LevelByte::egg))
			{

			}
			if (levelByte & static_cast<char>(LevelByte::pepper))
			{

			}
			if (levelByte & static_cast<char>(LevelByte::salt))
			{

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