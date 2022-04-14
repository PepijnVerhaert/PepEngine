#pragma once
#include "Singleton.h"
#include <string>
#include <vector>
#include <memory>

namespace pep
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene* CreateScene(const std::string& name);
		void RemoveScene(const std::string& name);

		Scene* GetScene(const std::string& name);

		Scene* SetSceneActive(const std::string& name);
		void SetSceneInactive(const std::string& name);

		void Update();
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::shared_ptr<Scene>> m_pScenes;
		std::vector<std::shared_ptr<Scene>> m_pActiveScenes;
	};
}
