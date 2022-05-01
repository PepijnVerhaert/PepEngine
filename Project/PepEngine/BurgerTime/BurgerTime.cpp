
#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include <functional>

#include "Engine.h"
#include "SceneManager.h"

void LoadGame()
{
	pep::SceneManager::GetInstance().CreateScene("Test");
}

int main(int, char* []) {
	std::function<void()> loadGame = LoadGame;
	pep::Engine pepEngine;
	pepEngine.Run(loadGame);
	return 0;
}