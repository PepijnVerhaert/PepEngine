#include "PepEnginePCH.h"
#include "TextureComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Object.h"

pep::TextureComponent::TextureComponent(const std::weak_ptr<Object>& object, const std::string& filename)
	:BaseComponent(object)
	, m_pTexture{ ResourceManager::GetInstance().LoadTexture(filename) }
	, m_IsVisible{ true }
	, m_Width{}
	, m_Height{}
	,m_DifferentSize{false}
{
	Renderer::GetInstance().GetTextureSize(*m_pTexture, m_Width, m_Height);
}

pep::TextureComponent::TextureComponent(const std::weak_ptr<Object>& object, const std::string& filename, int width, int height)
	:BaseComponent(object)
	, m_pTexture{ ResourceManager::GetInstance().LoadTexture(filename) }
	, m_IsVisible{ true }
	, m_Width{ width }
	, m_Height{ height }
	, m_DifferentSize{ true }
{
}

void pep::TextureComponent::Update()
{
}

void pep::TextureComponent::Render() const
{
	if (m_pTexture && m_IsVisible)
	{
		glm::vec2 pos{ m_pObject.lock()->GetWorldTransform().GetPosition() };
		if (m_DifferentSize)
		{
			Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y, m_Width, m_Height);
		}
		else
		{
			Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y);
		}
	}
}

void pep::TextureComponent::SetVisibility(bool isVisible)
{
	m_IsVisible = isVisible;
}
