#include "PepEnginePCH.h"
#include "Scene.h"
#include "Object.h"

using namespace pep;

Scene::Scene(const std::string& name) : m_Name(name) {}

void Scene::Add(const std::shared_ptr<Object>&pObject)
{
	for (auto& object : m_Objects)
	{
		if (object == pObject)
		{
			return;
		}
	}
	m_Objects.push_back(pObject);
}

void Scene::Remove(const std::shared_ptr<Object>& pObject)
{
	for (auto& object : m_Objects)
	{
		if (object == pObject)
		{
			object = nullptr;
		}
	}
}

const std::string& Scene::GetName() const
{
	return m_Name;
}

void Scene::Update()
{
	for (auto& object : m_Objects)
	{
		object->Update();
	}
}