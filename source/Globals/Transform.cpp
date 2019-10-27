#include "Transform.h"

EG::Transform::Transform()
	: rotation(Vector3D::Zero)
	, position(Vector3D::Zero)
	, scale(Vector3D(1.0f, 1.0f, 1.0f))
	, m_worldMatrix(Matrix::identity)
{
	
}

EG::Transform::~Transform()
{
	
}

void EG::Transform::Update()
{
	m_worldMatrix.ScaleRotateTranslate(scale, rotation, position, Matrix::CombineFunc::Replace);;
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
