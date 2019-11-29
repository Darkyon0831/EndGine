#pragma once
#include "Globals/Matrix.h"
#include "Globals/Transform.h"
#include <d3d11.h>
#include "Globals/Color.h"
#include "Globals/Vector2D.h"
#include "Globals/Frustum.h"

#include "ECS/Component.h"
#include <Graphics/Texture.h>
#include "Graphics/Mesh.h"

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

		CameraComponent(
			const float fov, 
			const float aspectRatio, 
			const float nearPlane, 
			const float farPlane, 
			const ProjectionType projectionType, 
			const Vector2D viewportSize, 
			const Vector2D viewportPos);

		~CameraComponent();
		
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

		Vector2D& GetViewportSize() { return m_viewportSize; }
		void SetViewportSize(const Vector2D& viewportSize) { m_viewportSize = viewportSize; }

		Vector2D& GetViewportPos() { return m_viewportPos; }
		void SetViewportPos(const Vector2D& viewportPos) { m_viewportPos = viewportPos; }

		const Texture* GetTexture() const { return m_texture; };
		
	private:

		void BeginRender(unsigned int clearFlags) const;
		void EndRender();

		Frustum m_frustum;
		
		ProjectionType m_projection;
		Transform m_transform;
		
		Vector2D m_viewportSize;
		Vector2D m_viewportPos;
		
		Color m_clearColor;

		ID3D11RenderTargetView* m_pRenderTarget;
		ID3D11DepthStencilView* m_pDepthStencil;
		ID3D11Texture2D* m_pDepthBuffer;
		D3D11_VIEWPORT m_viewPort;

		Texture* m_texture;

		float m_fov;
		float m_aspectRatio;
		float m_nearPlane;
		float m_farPlane;
	};
}
