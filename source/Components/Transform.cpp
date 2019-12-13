#include "Transform.h"

EG::Transform::Transform()
	: rotation(Vector3D::Zero)
	, position(Vector3D::Zero)
	, scale(Vector3D(1.0f, 1.0f, 1.0f))
	, m_worldMatrix(Matrix::identity)
{

}

EG::Transform::~Transform()
= default;

void EG::Transform::Update()
{
	m_worldMatrix.ScaleRotateTranslate(scale, rotation, position, Matrix::CombineFunc::Replace);
}

void EG::Transform::operator+=(const Transform& rTransform)
{
	position += rTransform.position;
	scale += rTransform.scale;
	rotation += rTransform.rotation;
}

EG::Transform EG::Transform::operator+(const Transform& rTransform) const
{
	Transform transform;
	transform.position = rTransform.position + position;
	transform.rotation = rTransform.rotation + rotation;
	transform.scale = rTransform.scale + scale;

	return transform;
}

EG::Vector3D EG::Transform::GetForward()
{
	Vector3D forward;
	forward.Set(m_worldMatrix[2], m_worldMatrix[6], m_worldMatrix[10]);
	forward.Normilize();

	return forward;
}

EG::Vector3D EG::Transform::GetUp()
{
	Vector3D up;
	up.Set(m_worldMatrix[1], m_worldMatrix[5], m_worldMatrix[9]);
	up.Normilize();

	return up;
}

EG::Vector3D EG::Transform::GetRight()
{
	Vector3D right;
	right.Set(m_worldMatrix[0], m_worldMatrix[4], m_worldMatrix[8]);
	right.Normilize();

	return right;
}
