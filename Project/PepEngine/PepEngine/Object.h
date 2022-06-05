#pragma once
#include "BaseComponent.h"
#include "Transform2D.h"
#include <vector>
#include <memory>

namespace pep
{
	class Object final
	{
	public:
		Object();
		~Object() = default;
		Object(const Object& other) = delete;
		Object(Object&& other) = delete;
		Object& operator=(const Object& other) = delete;
		Object& operator=(Object&& other) = delete;

		void SetParent(std::shared_ptr<Object> pChild, std::shared_ptr<Object> pParent, bool keepWorldTransform);
		
		void SetLocalTransform(const Transform2D& transform);
		const Transform2D& GetWorldTransform();
		const Transform2D& GetLocalTransform() const;
		void UpdateWorldTransform();
		void SetTransformDirty();

		void AddComponent(const std::shared_ptr<BaseComponent>& pNewComponent);
		void RemoveComponent(const std::shared_ptr<BaseComponent>& pComponent);
		template <class T>
		std::shared_ptr<T> GetComponent()
		{
			const type_info& ti = typeid(T);
			for (std::shared_ptr<BaseComponent> component : m_pComponents)
			{
				if (component && typeid(*component) == ti)
				{
					return std::static_pointer_cast<T, BaseComponent>(component);
				}
			}

			return nullptr;
		}

		void Update();
		void Render() const;

	private:
		void RemoveChild(std::shared_ptr<Object> pChild);
		void AddChild(std::shared_ptr<Object> pChild);

		bool m_Started;
		bool m_Ended;

		bool m_IsTransformDirty;
		Transform2D m_WorldTransform;
		Transform2D m_LocalTransform;

		std::vector<std::shared_ptr<BaseComponent>> m_pComponents;
		std::weak_ptr<Object> m_pParent;
		std::vector<std::shared_ptr<Object>> m_pChildren;
	};
}