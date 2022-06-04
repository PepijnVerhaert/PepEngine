
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
#include "SceneManager.h"
#include "Scene.h"
#include "Object.h"
#include "InputManager.h"
#include "SoundInclude.h"

//game includes
#include "TestComponent.h"
#include "TestCommand.h"

void LoadGame()
{
	pep::ServiceLocator::GetSoundService()->SetFilePath("../Data/");
	pep::ServiceLocator::GetSoundService()->PlayMusic("Boenkus.mp3", true, 30);
	auto& scene = pep::SceneManager::GetInstance().CreateScene("Test");
	auto testObject = std::make_shared<pep::Object>();
	testObject->AddComponent(std::make_shared<TestComponent>(testObject));
	scene.Add(testObject);

	pep::InputManager::GetInstance().AddControllerCommand(pep::ControllerButton::Button_South, pep::ButtonState::PressedThisFrame, std::make_shared<TestCommand>(testObject.get()), 0);
}

int main(int, char* []) {
	std::function<void()> loadGame = LoadGame;
	pep::Engine pepEngine;
	pepEngine.Run(loadGame);
	return 0;
}