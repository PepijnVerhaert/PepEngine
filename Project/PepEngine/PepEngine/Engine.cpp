#include "PepEnginePCH.h"
#include "Engine.h"

#include "Renderer.h"
#include "ResourceManager.h"
#include "Time.h"
#include "SceneManager.h"
#include "InputManager.h"

#include <thread>
#include <memory>

using namespace pep;

void PrintSDLVersion()
{
	SDL_version compiled{};
	SDL_version linked{};

	SDL_VERSION(&compiled);
	SDL_GetVersion(&linked);
	printf("We compiled against SDL version %d.%d.%d ...\n",
		compiled.major, compiled.minor, compiled.patch);
	printf("We are linking against SDL version %d.%d.%d.\n",
		linked.major, linked.minor, linked.patch);
}

void pep::Engine::Initialize()
{
	PrintSDLVersion();

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_Window = SDL_CreateWindow(
		"PepEngine",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(m_Window);
}

void pep::Engine::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void pep::Engine::Run(const std::function<void()>& loadGame)
{
	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");

	loadGame();

	{
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();

		bool quit = false;
		int msPerFrame = 16;
		auto lastTime = std::chrono::high_resolution_clock::now();
		auto start = std::chrono::high_resolution_clock::now();
		while (!quit)
		{
			auto currentTime = std::chrono::high_resolution_clock::now();
			Time::GetInstance().SetDeltaTime(std::chrono::duration<float>(currentTime - lastTime).count());

			input.Update();
			quit = input.QuitGame();

			sceneManager.Update();
			renderer.Render();

			lastTime = currentTime;

			const auto sleeptime = start + std::chrono::milliseconds(msPerFrame) - std::chrono::high_resolution_clock::now();
			std::this_thread::sleep_for(sleeptime);
		}
	}


	Cleanup();
}
