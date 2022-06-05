
#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include <functional>
#include <memory>

//engine includes
#include "Engine.h"
#include "SoundInclude.h"

//game includes
#include "ScenePrefab.h"

void LoadGame()
{
	pep::ServiceLocator::GetSoundService()->SetFilePath("../Data/Sound/");
	pep::ServiceLocator::GetSoundService()->PlayMusic("BMG_Level1.mp3", true, 30);
	CreateTestScene();
}

int main(int, char* []) {
	std::function<void()> loadGame = LoadGame;
	pep::Engine pepEngine;
	pepEngine.Run(loadGame);
	return 0;
}