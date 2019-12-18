#pragma once

#include "Globals/Vector3D.h"
#include "Globals/Matrix.h"
#include "ECS/Component.h"

namespace EG
{
	class Transform : public Component<Transform>
	{
	public:
		Transform();
		~Transform();

		void Update() override;
		Matrix& GetWorldMatrix() { return m_worldMatrix; }

		void operator+=(const Transform& rTransform);
		Transform operator+(const Transform& rTransform) const;

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
