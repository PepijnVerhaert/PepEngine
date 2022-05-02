#pragma once
#include <memory>
#include <string>

namespace pep
{
	class Object;
	class BaseComponent
	{
	public:
		BaseComponent(const std::weak_ptr<Object>& object) { m_pObject = object;};
		virtual ~BaseComponent() = default;
		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) = delete;

		virtual void Update() = 0;
	protected:
		std::weak_ptr<Object> m_pObject;
	};
}