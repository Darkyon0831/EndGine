#pragma once

#define _USE_MATH_DEFINES
#include  <math.h>

#include  "Vector3D.h"

namespace EG
{
	class Matrix
	{
	public:

		enum CombineFunc
		{
			Replace,
			PreMultiply,
			PostMultiply
		};
		
		Matrix() = default;
		Matrix(
			float _11, float _12, float _13, float _14,
			float _21, float _22, float _23, float _24,
			float _31, float _32, float _33, float _34,
			float _41, float _42, float _43, float _44
		);

		void RotateX(float angle, CombineFunc combine);
		void RotateY(float angle, CombineFunc combine);
		void RotateZ(float angle, CombineFunc combine);
		void Rotate(Vector3D rotation, CombineFunc combine);
		void Translate(Vector3D translation, CombineFunc combine);
		void Scale(Vector3D scale, CombineFunc combine);

		void ScaleRotateTranslate(Vector3D scale, Vector3D rotate, Vector3D translate, CombineFunc combine);
		void ScaleRotate(Vector3D scale, Vector3D rotate, CombineFunc combine);
		void ScaleTranslate(Vector3D scale, Vector3D translate, CombineFunc combine);
		void RotateTranslate(Vector3D rotate, Vector3D translate, CombineFunc combine);

		Matrix& Transpose(bool createNew = false);

		void operator*= (Matrix& rMatrix);
		Matrix operator* (Matrix& rMatrix);

		void operator+= (Matrix& rMatrix);
		Matrix operator+ (Matrix& rMatrix);

		void operator-= (Matrix& rMatrix);
		Matrix operator- (Matrix& rMatrix);
		
		float& operator[] (int index) { return *(&m_11 + index); }

		void ApplyPerspectiveMatrix(float aspect, float fov, float nearPlane, float farPlane);
		void ApplyOrthoMatrix(float width, float height, float nearPlane, float farPlane);
		void ApplyOrthoMatrix(float l, float r, float b, float t, float nearPlane, float farPlane);
		void ApplyViewMatrix(Vector3D cameraPos, Vector3D cameraLookAt);
		
		static const Matrix& identity;
		
	private:
		float m_11 = 0, m_12 = 0, m_13 = 0, m_14 = 0;
		float m_21 = 0, m_22 = 0, m_23 = 0, m_24 = 0;
		float m_31 = 0, m_32 = 0, m_33 = 0, m_34 = 0;
		float m_41 = 0, m_42 = 0, m_43 = 0, m_44 = 0;
	};
}