#include "PepEnginePCH.h"
#include "Transform.h"
#include "Object.h"

using namespace pep;

Transform::Transform()
	:m_Transform{}
{
}

Transform::~Transform()
{
}

Transform::Transform(const Transform& other)
{
	SetTransform(other.GetTransform());
}

Transform& Transform::operator=(const Transform& other)
{
	SetTransform(other.GetTransform());
	return *this;
}

const Transform2D& Transform::GetTransform() const
{
	return m_Transform;
}

const Position2D& Transform::GetPosition() const
{
	return m_Transform.position;
}

const Scale2D& Transform::GetScale() const
{
	return m_Transform.scale;
}

const Rotation2DDEG& Transform::GetRotation() const
{
	return m_Transform.rotation;
}

void Transform::SetPosition(const Position2D& position)
{
	m_Transform.position = position;
}

void Transform::SetScale(const Scale2D& scale)
{
	m_Transform.scale = scale;
}

void Transform::SetRotation(const Rotation2DDEG& rotation)
{
	m_Transform.rotation = rotation;
}

void Transform::SetTransform(const Transform2D& transform)
{
	m_Transform = transform;
}

