#include "PepEnginePCH.h"
#include "Transform2D.h"
#include "Object.h"

using namespace pep;

Transform2D::Transform2D()
	:Transform2D{ {0.f, 0.f}/*, {1.f, 1.f}, 0.f*/ }
{
}

Transform2D::Transform2D(const glm::vec2& position)
	: m_Position {position}
{
}

//Transform2D::Transform2D(const glm::vec3& position, const glm::vec2& scale, float rotation)
//	:m_Position{ position }
//	, m_Scale{ scale }
//	, m_Rotation{ rotation }
//{
//}

Transform2D::Transform2D(const Transform2D& other)
{
	m_Position = other.GetPosition();
	//m_Scale = other.GetScale();
	//m_Rotation = other.GetRotation();
}

Transform2D& Transform2D::operator=(const Transform2D& other)
{
	m_Position = other.m_Position;
	//m_Scale = other.m_Scale;
	//m_Rotation = other.m_Rotation;
	return *this;
}

const glm::vec2& Transform2D::GetPosition() const
{
	return m_Position;
}

//const glm::vec2& Transform2D::GetScale() const
//{
//	return m_Scale;
//}

//float Transform2D::GetRotation() const
//{
//	return m_Rotation;
//}

void Transform2D::SetPosition(const glm::vec2& position)
{
	m_Position = position;
}

void Transform2D::SetPosition(float x, float y)
{
	SetPosition({ x, y});
}

//void Transform2D::SetScale(const glm::vec2& scale)
//{
//	m_Scale = scale;
//}

//void Transform2D::SetScale(float x, float y)
//{
//	SetScale({ x, y});
//}

//void Transform2D::SetScale(float uniformScale)
//{
//	SetScale({ uniformScale, uniformScale});
//}

//void Transform2D::SetRotation(float rotation)
//{
//	m_Rotation = rotation;
//}
