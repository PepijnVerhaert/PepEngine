#pragma once
#include "BaseComponent.h"

namespace pep
{
	class TextureComponent final : public BaseComponent
	{
	public:
		TextureComponent(const std::weak_ptr<Object>& object);
		~TextureComponent() = default;
		TextureComponent(const TextureComponent& other) = delete;
		TextureComponent(TextureComponent&& other) = delete;
		TextureComponent& operator=(const TextureComponent& other) = delete;
		TextureComponent& operator=(TextureComponent&& other) = delete;

		void Update();

	private:

	};
}
