#include "PepEnginePCH.h"
#include "SceneManager.h"
#include "Scene.h"

using namespace pep;

void SceneManager::Update()
{
	for (size_t i{}; i < m_pActiveScenes.size(); ++i)
	{
		m_pActiveScenes[i]->Update();
	}
}

void pep::SceneManager::Render() const
{
	for (size_t i{}; i < m_pVisibleScenes.size(); ++i)
	{
		m_pVisibleScenes[i]->Render();
	}
}

Scene* SceneManager::CreateScene(const std::string& name)
{
	//if scene with name already exists return that scene
	Scene* scene = GetScene(name);
	if (scene != nullptr)
	{
		return scene;
	}
	//otherwise create new scene and return it
	for (size_t i{}; i < m_pScenes.size(); ++i)
	{
		if (m_pScenes[i] == nullptr)
		{
			//cant use make shared since only scenemanager is friended with scene
			m_pScenes[i] = std::shared_ptr<Scene>( new Scene(name));
			return m_pScenes[i].get();
		}
	}
	//scenes vector was full
	//cant use make shared since only scenemanager is friended with scene
	m_pScenes.emplace_back(std::shared_ptr<Scene>(new Scene(name)));
	return m_pScenes.back().get();
}

Scene* SceneManager::GetScene(const std::string& name)
{
	for (size_t i{}; i < m_pScenes.size(); ++i)
	{
		if (m_pScenes[i] == nullptr)
		{
			continue;
		}

		if (m_pScenes[i]->GetName() == name)
		{
			return m_pScenes[i].get();
		}
	}
	//scene was not found
	return nullptr;
}

void pep::SceneManager::SetSceneInactive(const std::string& name)
{
	for (size_t i{}; i < m_pActiveScenes.size(); ++i)
	{
		if (m_pActiveScenes[i] == nullptr)
		{
			continue;
		}
		//find the right scene
		if (m_pActiveScenes[i]->GetName() == name)
		{
			m_pActiveScenes[i] = nullptr;
			return;
		}
	}
	//scene was not active
}

Scene* pep::SceneManager::SetSceneVisible(const std::string& name)
{
	for (size_t i{}; i < m_pScenes.size(); ++i)
	{
		if (m_pScenes[i] == nullptr)
		{
			continue;
		}
		//find the right scene
		if (m_pScenes[i]->GetName() == name)
		{
			for (size_t j{}; j < m_pVisibleScenes.size(); ++j)
			{
				if (m_pVisibleScenes[j] != nullptr)
				{
					continue;
				}
				//find empty slot to assign
				m_pVisibleScenes[j] = m_pScenes[i];
				return m_pVisibleScenes[j].get();
			}
			//if there was no empty slot push back
			m_pVisibleScenes.push_back(m_pScenes[i]);
			return m_pVisibleScenes.back().get();
		}
	}
	//right scene was not found
	return nullptr;
}

void pep::SceneManager::SetSceneInvisible(const std::string& name)
{
	for (size_t i{}; i < m_pVisibleScenes.size(); ++i)
	{
		if (m_pVisibleScenes[i] == nullptr)
		{
			continue;
		}
		//find the right scene
		if (m_pVisibleScenes[i]->GetName() == name)
		{
			m_pVisibleScenes[i] = nullptr;
			return;
		}
	}
	//scene was not visible
}

Scene* pep::SceneManager::SetSceneActive(const std::string& name)
{
	for (size_t i{}; i < m_pScenes.size(); ++i)
	{
		if (m_pScenes[i] == nullptr)
		{
			continue;
		}
		//find the right scene
		if (m_pScenes[i]->GetName() == name)
		{
			for (size_t j{}; j < m_pActiveScenes.size(); ++j)
			{
				if (m_pActiveScenes[j] != nullptr)
				{
					continue;
				}
				//find empty slot to assign
				m_pActiveScenes[j] = m_pScenes[i];
				return m_pActiveScenes[j].get();
			}
			//if there was no empty slot push back
			m_pActiveScenes.push_back(m_pScenes[i]);
			return m_pActiveScenes.back().get();
		}
	}
	//right scene was not found
	return nullptr;
}

void SceneManager::RemoveScene(const std::string& name)
{
	//remove from scenes
	for (size_t i{}; i < m_pScenes.size(); ++i)
	{
		if (m_pScenes[i] == nullptr)
		{
			continue;
		}

		if (m_pScenes[i]->GetName() == name)
		{
			m_pScenes[i] = nullptr;
		}
	}
	//remove from active scenes
	for (size_t i{}; i < m_pActiveScenes.size(); ++i)
	{
		if (m_pActiveScenes[i] == nullptr)
		{
			continue;
		}

		if (m_pActiveScenes[i]->GetName() == name)
		{
			m_pActiveScenes[i] = nullptr;
		}
	}
}