#pragma once
#include "Singleton.h"
#include "Shapes.h"

struct SDL_Window;
struct SDL_Renderer;

namespace pep
{
	class Texture2D;
	/**
	 * Simple RAII wrapper for the SDL renderer
	 */
	class Renderer final : public Singleton<Renderer>
	{
	public:
		void Init(SDL_Window* window);
		void Render() const;
		void Destroy();

		void GetWindowSize(int& width, int& height) const;

		void GetTextureSize(const Texture2D& texture, int& width, int& height) const;

		void RenderTexture(const Texture2D& texture, const float x, const float y) const;
		void RenderTexture(const Texture2D& texture, const float x, const float y, int width, int height) const;
		void RenderTexture(const Texture2D& texture, const Rectangle& dst) const;
		void RenderTexture(const Texture2D& texture, const Rectangle& src, const Rectangle& dst) const;
		void RenderTexture(const Texture2D& texture, const Rectangle& src, const Rectangle& dst, float angleDEG) const;

		SDL_Renderer* GetSDLRenderer() const { return m_Renderer; }
	private:
		friend class Singleton<Renderer>;
		Renderer() = default;
		SDL_Renderer* m_Renderer{};
		SDL_Window* m_Window{};
	};
}

