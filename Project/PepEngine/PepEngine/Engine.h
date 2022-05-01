#pragma once
#include <functional>

struct SDL_Window;
namespace pep
{
	class Engine final
	{
	public:
		void Initialize();
		void Cleanup();
		void Run(const std::function<void()>& loadGame);
	private:
		static const int MsPerFrame = 16; //16 for 60 fps, 33 for 30 fps
		SDL_Window* m_Window{};
	};
}