#pragma once

#include "Matrix.h"

namespace EG
{
	class Transform
	{
	public:
		Transform();
		~Transform();

		void Update();
		Matrix& GetWorldMatrix() { return m_worldMatrix; }

		Vector3D GetForward();
		Vector3D GetUp();
		Vector3D GetRight();
		
		Vector3D rotation;
		Vector3D position;
		Vector3D scale;

	private:
		Matrix m_worldMatrix;
	};
}