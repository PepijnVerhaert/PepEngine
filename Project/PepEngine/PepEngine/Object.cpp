#include "PepEnginePCH.h"
#include "Object.h"
#include <algorithm>

using namespace pep;

Object::Object()
	: m_pComponents{}
	, m_pParent{ nullptr }
	, m_pChildren{}
{
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

void Object::SetParent(Object* pParent, bool keepWorldPosition)
{
	//Update position, rotation and scale
	if (pParent == nullptr)
		SetLocalTransform(GetWorldTransform());
	else
	{
		if (keepWorldPosition)
			SetLocalTransform(GetLocalTransform() - pParent->GetWorldTransform());
		SetTransformDirty();
	}
	//Remove itself as a child from the previous parent (if any) 
	if (m_pParent)
		m_pParent->RemoveChild(this);
	//Set the given parent on itself
	m_pParent = pParent;
	//Add itself as a child to the given parent
	if (m_pParent)
		m_pParent->AddChild(this);
}

void Object::SetTransformDirty()
{
	m_IsTransformDirty = true;
}

void Object::RemoveChild(Object* pChild)
{
}

void Object::AddChild(Object* pChild)
{
}

void Object::SetLocalTransform(const glm::vec3& pos)
{
}

const Transform2D& Object::GetWorldTransform()
{
	if (m_IsTransformDirty)
	{
		UpdateWorldTransform();
	}
	return m_WorldTransform;
}

const Transform2D& Object::GetLocalTransform() const
{
	return m_LocalTransform;
}

void Object::UpdateWorldTransform()
{
	if (m_IsTransformDirty)
	{
		if (m_pParent == nullptr)
			m_WorldTransform = m_LocalTransform;
		else
			m_WorldTransform = m_pParent->GetWorldTransform() + m_LocalTransform;
	}
	m_IsTransformDirty = false;
}
