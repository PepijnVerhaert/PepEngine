#include "PepEnginePCH.h"
#include "Scene.h"
#include "Object.h"

using namespace pep;

Scene::Scene(const std::string& name)
	: m_Name(name) 
	, m_pObjects()
{
}

void Scene::Add(const std::shared_ptr<Object>&pObject)
{
	//check if it's already in there
	for (size_t i{}; i < m_pObjects.size(); ++i)
	{
		if (m_pObjects[i] == pObject)
		{
			return;
		}
	}

	//look for empty spot
	for (size_t i{}; i < m_pObjects.size(); ++i)
	{
		if (m_pObjects[i] == nullptr)
		{
			m_pObjects[i] = pObject;
			return;
		}
	}

	//no empty spot found
	m_pObjects.push_back(pObject);
}

void Scene::Remove(const std::shared_ptr<Object>& pObject)
{
	for (size_t i{}; i < m_pObjects.size(); ++i)
	{
		if (m_pObjects[i] == pObject)
		{
			m_pObjects[i] = nullptr;
			return;
		}
	}
}

const std::string& Scene::GetName() const
{
	return m_Name;
}

void Scene::Update()
{
	for (size_t i{}; i < m_pObjects.size(); ++i)
	{
		m_pObjects[i]->Update();
	}
}

void pep::Scene::Render() const
{
	for (size_t i{}; i < m_pObjects.size(); ++i)
	{
		m_pObjects[i]->Render();
	}
}
