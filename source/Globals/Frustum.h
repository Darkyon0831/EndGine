#pragma once

#include "Globals/Vector3D.h"
#include "Globals/Vector2D.h"
#include "Globals/Transform.h"

#define NUMPLANES 6

namespace EG
{
	class Frustum
	{
	public:
		struct FrustumPlane
		{
			Vector3D bottomLeftCorner;
			Vector3D upperLeftCorner;
			Vector3D bottomRightCorner;
			Vector3D upperRightCorner;
		};

		Frustum() = default;
		Frustum(const float& nearZ, const float& farZ, Transform& transform, const float& aspectRatio, const float& fov);
		
		~Frustum() = default;
		
		void Update(const float& nearZ, const float& farZ, Transform& transform, const float& aspectRatio, const float& fov);

		bool IsPointInside(const Vector3D& rPoint) const;
		
	private:

		void CalculateFrustum(const float& nearZ, const float& farZ, Transform& transform, const float& aspectRatio, const float& fov);
		
		FrustumPlane m_nearPlane;
		FrustumPlane m_farPlane;
		
		Vector3D m_planeNormals[NUMPLANES];
	};
}