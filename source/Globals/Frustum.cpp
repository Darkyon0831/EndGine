#include "Frustum.h"

#include <cmath>

//EG::Frustum::Frustum(const float& nearZ, const float& farZ, Transform& transform, const float& aspectRatio,
//	const float& fov)
//{
//	CalculateFrustum(nearZ, farZ, transform, aspectRatio, fov);
//}
//
//void EG::Frustum::Update(
//	const float& nearZ, 
//	const float& farZ, 
//	Transform& transform, 
//	const float& aspectRatio,
//	const float& fov)
//{
//	CalculateFrustum(nearZ, farZ, transform, aspectRatio, fov);
//}
//
//bool EG::Frustum::IsPointInside(const Vector3D& rPoint) const
//{
//	const Vector3D toPoint = rPoint - m_nearPlane.bottomRightCorner;
//
//	for (unsigned int i = 0; i < NUMPLANES; i++)
//	{
//		const float dotProtuct = toPoint.DotProduct(m_planeNormals[i]);
//
//		if (dotProtuct < 0)
//			return false;
//	}
//
//	return true;
//}
//
//void EG::Frustum::CalculateFrustum(const float& nearZ, const float& farZ, Transform& transform,
//	const float& aspectRatio, const float& fov)
//{
//	const Vector3D& transformForward = transform.GetForward();
//	const Vector3D& transformUp = transform.GetUp();
//	const Vector3D& transformRight = transform.GetRight();
//	const Vector3D& transformPos = transform.position;
//
//	// Calculate far plane and near plane middle points
//
//	const Vector3D nearMiddle = (transformPos + transformForward) * nearZ;
//	const Vector3D farMiddle = (transformPos + transformForward) * farZ;
//
//	// Calculate half width and half height of planes
//
//	Vector2D nearHalfSize;
//	nearHalfSize.y = tan(fov / 2.0f) * nearZ;
//	nearHalfSize.x = nearHalfSize.y * aspectRatio;
//
//	Vector2D farHalfSize;
//	farHalfSize.y = tan(fov / 2.0f) * farZ;
//	farHalfSize.x = farHalfSize.y * aspectRatio;
//
//	// Calculate plane corners
//
//	m_nearPlane.bottomLeftCorner = nearMiddle - transformRight * nearHalfSize.x - transformUp * nearHalfSize.y;
//	m_nearPlane.upperLeftCorner = nearMiddle - transformRight * nearHalfSize.x + transformUp * nearHalfSize.y;
//	m_nearPlane.bottomRightCorner = nearMiddle + transformRight * nearHalfSize.x - transformUp * nearHalfSize.y;
//	m_nearPlane.upperRightCorner = nearMiddle + transformRight * nearHalfSize.x + transformUp * nearHalfSize.y;
//
//	m_farPlane.bottomLeftCorner = farMiddle - transformRight * farHalfSize.x - transformUp * farHalfSize.y;
//	m_farPlane.upperLeftCorner = farMiddle - transformRight * farHalfSize.x + transformUp * farHalfSize.y;
//	m_farPlane.bottomRightCorner = farMiddle + transformRight * farHalfSize.x - transformUp * farHalfSize.y;
//	m_farPlane.upperRightCorner = farMiddle + transformRight * farHalfSize.x + transformUp * farHalfSize.y;
//
//	// Calculate all frustum planes normal
//
//	// (NUR - NUL) X (NBR - NUR)
//
//	m_planeNormals[0] = Vector3D::CrossProduct(m_nearPlane.upperRightCorner - m_nearPlane.upperLeftCorner, m_nearPlane.bottomRightCorner - m_nearPlane.upperRightCorner);
//	m_planeNormals[0].Normilize();
//
//	// (FUR - NUR) X (FBR - FUR)
//
//	m_planeNormals[1] = Vector3D::CrossProduct(m_farPlane.upperRightCorner - m_nearPlane.upperRightCorner, m_farPlane.bottomRightCorner - m_farPlane.upperRightCorner);
//	m_planeNormals[1].Normilize();
//
//	// (FBL - NBL) X (FBR - FBL)
//
//	m_planeNormals[2] = Vector3D::CrossProduct(m_farPlane.bottomLeftCorner - m_nearPlane.bottomLeftCorner, m_farPlane.bottomRightCorner - m_farPlane.bottomLeftCorner);
//	m_planeNormals[2].Normilize();
//
//	// (FUL - NUL) X (FBL - FUL)
//
//	m_planeNormals[3] = Vector3D::CrossProduct(m_farPlane.upperLeftCorner - m_nearPlane.upperLeftCorner, m_farPlane.bottomLeftCorner - m_farPlane.upperLeftCorner);
//	m_planeNormals[3].Normilize();
//
//	// (FUR - FUL) X (NUR - FUR)
//
//	m_planeNormals[4] = Vector3D::CrossProduct(m_farPlane.upperRightCorner - m_farPlane.upperLeftCorner, m_nearPlane.upperRightCorner - m_farPlane.upperRightCorner);
//	m_planeNormals[4].Normilize();
//
//	// (FUR - FUL) X (FBR - FUR)
//
//	m_planeNormals[5] = Vector3D::CrossProduct(m_farPlane.upperRightCorner - m_farPlane.upperLeftCorner, m_farPlane.bottomRightCorner - m_farPlane.upperRightCorner);
//	m_planeNormals[5].Normilize();
//}
