#include "PepEnginePCH.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "Scene.h"

using namespace pep;

void SceneManager::Update()
{
	m_pCurrentScene->Update();
}

void SceneManager::Render()
{
	m_pCurrentScene->Render();
}

Scene& SceneManager::CreateScene(const std::string& name)
{
	for (size_t i{}; i < m_pScenes.size(); ++i)
	{
		if (m_pScenes[i] != nullptr)
		{
			if (m_pScenes[i].get()->GetName() == name)
			{
				std::cout << std::string{ "scene with name: " + name + " already exists\n" };
				return *m_pScenes[i].get();
			}
		}
	}
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	m_pScenes.push_back(scene);
	if (m_pCurrentScene == nullptr)
	{
		m_pCurrentScene = m_pScenes[0];
	}
	return *scene;
}

bool SceneManager::GetScene(const std::string& name, std::shared_ptr<Scene>& pScene)
{
	for (size_t i{}; i < m_pScenes.size(); ++i)
	{
		if (m_pScenes[i] != nullptr)
		{
			if (m_pScenes[i].get()->GetName() == name)
			{
				pScene = m_pScenes[i];
				return true;
			}
		}
	}
	return false;
}

bool SceneManager::RemoveScene(const std::string& name)
{
	for (size_t i{}; i < m_pScenes.size(); ++i)
	{
		if (m_pScenes[i] != nullptr)
		{
			if (m_pScenes[i].get()->GetName() == name)
			{
				m_pScenes[i] = nullptr;
				return true;
			}
		}
	}
	return false;
}

void SceneManager::SetCurrentScene(const std::string& name)
{
	for (size_t i{}; i < m_pScenes.size(); ++i)
	{
		if (m_pScenes[i] != nullptr)
		{
			if (m_pScenes[i].get()->GetName() == name)
			{
				m_pCurrentScene = m_pScenes[i];
				return;
			}
		}
	}
	std::cout << std::string{ "scene with name: " + name + " not found\n" };
}
