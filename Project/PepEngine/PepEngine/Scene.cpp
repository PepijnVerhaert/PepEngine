#include "PepEnginePCH.h"
#include "Scene.h"
#include "Object.h"

using namespace pep;


Scene::Scene(const std::string& name) : m_Name(name) {}

Scene::~Scene() = default;

void Scene::Add(const std::shared_ptr<Object>&object)
{
	m_Objects.push_back(object);
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