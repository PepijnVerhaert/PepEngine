#include "PepEnginePCH.h"
#include "Object.h"
#include <algorithm>

using namespace pep;

Object::Object()
	: m_pComponents{}
	, m_Transform{}
	, m_pParent{ nullptr }
	, m_pChildren{}
{
}

const Transform& Object::GetTransform() const
{
	return m_Transform;
}

void Object::SetTransform(const Transform& transform)
{
	m_Transform = transform;
}

void Object::AddComponent(const std::shared_ptr<BaseComponent>& pNewComponent)
{
	if (!pNewComponent)
	{
		return;
	}

	for (std::shared_ptr<BaseComponent> pComponent : m_pComponents)
	{
		if (pComponent == pNewComponent)
		{
			return;
		}
	}

	m_pComponents.push_back(pNewComponent);
}

void Object::RemoveComponent(const std::shared_ptr<BaseComponent>& pComponent)
{
	if (!pComponent)
	{
		return;
	}

	auto it = find(m_pComponents.begin(), m_pComponents.end(), pComponent);

	if (it == m_pComponents.end())
	{
		return;
	}

	m_pComponents.erase(it);
}

void Object::Update()
{
	for (auto pComponent : m_pComponents)
	{
		pComponent->Update();
	}
}


void Object::Render()
{
	for (auto pComponent : m_pComponents)
	{
		pComponent->Render();
	}
}

void Object::SetParent(Object* pParent)
{
	m_pParent = pParent;
}

Object* Object::GetParent() const
{
	return m_pParent;
}

size_t Object::GetChildCount() const
{
	return m_pChildren.size();
}

Object* Object::GetChildAt(int index) const
{
	return m_pChildren.at(index);
}

void Object::RemoveChild(int index)
{
	m_pChildren.at(index) = nullptr;
}

void Object::AddChild(Object* pChild)
{
	m_pChildren.push_back(pChild);
}
