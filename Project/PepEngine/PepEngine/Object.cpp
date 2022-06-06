#include "PepEnginePCH.h"
#include "Object.h"
#include <algorithm>

using namespace pep;

Object::Object()
	: m_pComponents{}
	, m_pParent{}
	, m_pChildren{}
	, m_Started{ false }
	, m_Ended{ false }
	, m_IsTransformDirty{ true }
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
	for (auto pChild : m_pChildren)
	{
		pChild->Update();
	}
}

void pep::Object::Render() const
{
	for (auto pComponent : m_pComponents)
	{
		pComponent->Render();
	}
	for (auto pChild : m_pChildren)
	{
		pChild->Render();
	}
}

void Object::SetParent(std::shared_ptr<Object> pChild, std::shared_ptr<Object> pParent, bool keepWorldPosition)
{
	//Update position, rotation and scale
	if (pParent == nullptr)
	{
		SetLocalTransform(GetWorldTransform());
	}
	else
	{
		if (keepWorldPosition)
		{
			SetLocalTransform({ GetLocalTransform().GetPosition() - pParent->GetWorldTransform().GetPosition()});
		}
		SetTransformDirty();
	}
	//Remove itself as a child from the previous parent (if any) 
	auto pPreviousParent = m_pParent.lock();
	if (pPreviousParent)
	{
		pPreviousParent->RemoveChild(pChild);
	}
	//Set the given parent on itself
	m_pParent = pParent;
	//Add itself as a child to the given parent
	if (pParent)
	{
		pParent->AddChild(pChild);
	}
}

void Object::SetTransformDirty()
{
	m_IsTransformDirty = true;
}

void Object::RemoveChild(std::shared_ptr<Object> pChild)
{
	for (size_t i = 0; i < m_pChildren.size(); ++i)
	{
		if (m_pChildren[i] == pChild)
		{
			m_pChildren[i] = nullptr;
			return;
		}
	}
	//Remove the given child from the children list
}

void Object::AddChild(std::shared_ptr<Object> pChild)
{
	m_pChildren.push_back(pChild);
	//	• Add the child to its children list.
}

void Object::SetLocalTransform(const Transform2D& transform)
{
	m_LocalTransform.SetPosition(transform.GetPosition());
	SetTransformDirty();
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
		auto pParent = m_pParent.lock();
		if (pParent == nullptr)
			m_WorldTransform = m_LocalTransform;
		else
			m_WorldTransform.SetPosition(pParent->GetWorldTransform().GetPosition() + m_LocalTransform.GetPosition());
	}
	m_IsTransformDirty = false;
}
