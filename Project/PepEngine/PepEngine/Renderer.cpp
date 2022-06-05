#include "PepEnginePCH.h"
#include "Renderer.h"
#include <SDL.h>
#include "SceneManager.h"
#include "Texture2D.h"
#include "imgui.h"
#include "backends/imgui_impl_sdl.h"
#include "backends/imgui_impl_opengl2.h"

using namespace pep;

int GetOpenGLDriverIndex()
{
	auto openglIndex = -1;
	const auto driverCount = SDL_GetNumRenderDrivers();
	for (auto i = 0; i < driverCount; i++)
	{
		SDL_RendererInfo info;
		if (!SDL_GetRenderDriverInfo(i, &info))
			if (!strcmp(info.name, "opengl"))
				openglIndex = i;
	}
	return openglIndex;
}

void Renderer::Init(SDL_Window* window)
{
	m_Window = window;
	m_Renderer = SDL_CreateRenderer(window, GetOpenGLDriverIndex(), SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (m_Renderer == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(window, SDL_GL_GetCurrentContext());
	ImGui_ImplOpenGL2_Init();
}

void Renderer::Render() const
{
	SDL_RenderClear(m_Renderer);

	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplSDL2_NewFrame(m_Window);
	ImGui::NewFrame();

	SceneManager::GetInstance().Render();

	ImGui::Render();
	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

	SDL_RenderPresent(m_Renderer);
}

void Renderer::Destroy()
{
	ImGui_ImplOpenGL2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	if (m_Renderer != nullptr)
	{
		SDL_DestroyRenderer(m_Renderer);
		m_Renderer = nullptr;
	}
}

void Renderer::GetWindowSize(int& width, int& height) const
{
	SDL_GetWindowSize(m_Window, &width, &height);
}

void Renderer::GetTextureSize(const Texture2D& texture, int& width, int& height) const
{
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &width, &height);
}

void Renderer::RenderTexture(const Texture2D& texture, const float x, const float y) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, int width, int height) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = width;
	dst.h = height;
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void Renderer::RenderTexture(const Texture2D& texture, const Rectangle& dst) const
{
	SDL_Rect dstRect;
	dstRect.x = static_cast<int>(dst.x);
	dstRect.y = static_cast<int>(dst.y);
	dstRect.w = static_cast<int>(dst.width);
	dstRect.h = static_cast<int>(dst.height);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dstRect);
}

void Renderer::RenderTexture(const Texture2D& texture, const Rectangle& src, const Rectangle& dst) const
{
	RenderTexture(texture, src, dst, 0.f);
}

void Renderer::RenderTexture(const Texture2D& texture, const Rectangle& src, const Rectangle& dst, float angleDEG) const
{
	SDL_Rect srcRect;
	srcRect.x = static_cast<int>(src.x);
	srcRect.y = static_cast<int>(src.y);
	srcRect.w = static_cast<int>(src.width);
	srcRect.h = static_cast<int>(src.height);

	SDL_Rect dstRect;
	dstRect.x = static_cast<int>(dst.x);
	dstRect.y = static_cast<int>(dst.y);
	dstRect.w = static_cast<int>(dst.width);
	dstRect.h = static_cast<int>(dst.height);

	SDL_RenderCopyEx(GetSDLRenderer(), texture.GetSDLTexture(), &srcRect, &dstRect, static_cast<double>(angleDEG), nullptr, SDL_FLIP_NONE);
}
