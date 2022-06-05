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
	};
}
