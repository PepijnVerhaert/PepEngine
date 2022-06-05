#pragma once
#include "BaseComponent.h"
#pragma warning(push, 0)
#include <glm/glm.hpp>
#pragma warning (pop)

namespace pep
{
	class Transform2D final
	{
	public:
		Transform2D();
		Transform2D(const glm::vec2& position);
		//Transform2D(const glm::vec3& position, const glm::vec2& scale, float rotation);
		~Transform2D() = default;
		Transform2D(const Transform2D& other);
		Transform2D(Transform2D&& other) = delete;
		Transform2D& operator=(const Transform2D& other);
		Transform2D& operator=(Transform2D&& other) = delete;

		const glm::vec2& GetPosition() const;
		//const glm::vec2& GetScale() const;
		//float GetRotation() const;

		void SetPosition(const glm::vec2& position);
		void SetPosition(float x, float y);
		//void SetScale(const glm::vec2& scale);
		//void SetScale(float x, float y);
		//void SetScale(float uniformScale);
		//void SetRotation(float rotation);

	protected:
		glm::vec2 m_Position;
		//glm::vec2 m_Scale;
		//float m_Rotation;
	};
}