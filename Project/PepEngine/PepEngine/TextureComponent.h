#pragma once
#include "BaseComponent.h"
#include <string>

namespace pep
{
	class Texture2D;
	class TextureComponent final : public BaseComponent
	{
	public:
		TextureComponent(const std::weak_ptr<Object>& object, const std::string& filename);
		TextureComponent(const std::weak_ptr<Object>& object, const std::string& filename, int width, int height);
		~TextureComponent() = default;
		TextureComponent(const TextureComponent& other) = delete;
		TextureComponent(TextureComponent&& other) = delete;
		TextureComponent& operator=(const TextureComponent& other) = delete;
		TextureComponent& operator=(TextureComponent&& other) = delete;

		void Update() override;
		void Render() const override;

		void SetVisibility(bool isVisible);

	private:
		std::shared_ptr<Texture2D> m_pTexture{};
		bool m_IsVisible;
		bool m_DifferentSize;
		int m_Width;
		int m_Height;
	};
}
