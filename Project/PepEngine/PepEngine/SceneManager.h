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
		Scene& CreateScene(const std::string& name);
		bool GetScene(const std::string& name, std::shared_ptr<Scene>& pScene);
		bool RemoveScene(const std::string& name);
		void SetCurrentScene(const std::string& name);

		void Update();
		void Render();
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::shared_ptr<Scene>> m_pScenes;
		std::shared_ptr<Scene> m_pCurrentScene;
	};
}
