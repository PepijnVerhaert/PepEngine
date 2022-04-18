#pragma once
#include "SceneManager.h"
#include <memory>

namespace pep
{
	class Object;
	class Scene final
	{
		friend Scene* SceneManager::CreateScene(const std::string& name);
	public:
		void Add(const std::shared_ptr<Object>& pObject);
		void Remove(const std::shared_ptr<Object>& pObject);
		const std::string& GetName() const;

		void Update();

		~Scene() = default;
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private:
		explicit Scene(const std::string& name);

		std::string m_Name;
		std::vector < std::shared_ptr<Object>> m_Objects{};
	};

}
