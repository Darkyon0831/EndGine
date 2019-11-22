#pragma once
#include "Globals/Matrix.h"
#include "Globals/Transform.h"
#include <d3d11.h>
#include "Globals/Color.h"
#include "Globals/Vector2D.h"
#include "Globals/Frustum.h"

#include "ECS/Component.h"

namespace EG
{
	class Vector2D;

	class CameraComponent : public Component<CameraComponent>
	{
	public:

		friend class RenderQueue;
		
		enum ProjectionType
		{
			Perspective,
			Orthogonal
		};

		enum ClearFlags
		{
			RenderTarget = 1 << 0,
			Stencil = 1 << 1,
			Depth = 1 << 2
		};

		CameraComponent(float fov, float aspectRatio, float nearPlane, float farPlane, ProjectionType projectionType, Vector2D viewportStart, Vector2D viewportSize);
		
		void Update() override;

		Transform& GetTransform() { return m_transform; }

		Matrix GetViewMatrix();
		Matrix GetProjectionMatrix() const;
		Matrix GetViewProjectionMatrix();

		float& GetFov() { return m_fov; }
		void SetFov(const float fov) { m_fov = fov; }

		float& GetAspectRatio() { return m_aspectRatio; }
		void SetAspectRatio(const float& aspectRatio) { m_aspectRatio = aspectRatio; }

		float& GetNearPlane() { return m_nearPlane; }
		void SetNearPlane(const float& nearPlane) { m_nearPlane = nearPlane; }

		float& GetFarPlane() { return m_farPlane; }
		void SetFarPlane(const float& farPlane) { m_farPlane = farPlane; }

		ProjectionType& GetProjectionType() { return m_projection; }
		void SetProjectionType(const ProjectionType projectionType) { m_projection = projectionType; }

		void SetClearColor(const Color& color) { m_clearColor = color; }
		Color& GetClearColor() { return m_clearColor; }
		
	private:

		void BeginRender(unsigned int clearFlags) const;

		Frustum m_frustum;
		
		ProjectionType m_projection;
		Transform m_transform;
		Vector2D m_viewportSize;
		Vector2D m_viewportStart;

		Color m_clearColor;

		ID3D11RenderTargetView* m_pRenderTarget;
		ID3D11DepthStencilView* m_pDepthStencil;
		ID3D11Texture2D* m_pDepthBuffer;
		D3D11_VIEWPORT m_viewPort;

		float m_fov;
		float m_aspectRatio;
		float m_nearPlane;
		float m_farPlane;
	};
}
