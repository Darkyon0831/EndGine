#pragma once

#include  <d3d11.h>
#include  <DirectXMath.h>

#include "Matrix.h"
#include "Transform.h"
#include "Macro.h"
#include "Settings/WndSettings.h"
#include "Graphics/Device.h"
#include "Graphics/SwapChain.h"
#include "Vector2D.h"
#include "Color.h"

namespace EG
{
	class Camera
	{
	public:
		enum ProjectionType
		{
			Perspective,
			Orthogonal
		};

		enum ClearFlags
		{
			RenderTarget = 1 << 0,
			Sencil = 1 << 1,
			Depth = 1 << 2
		};
		
		Camera(float fov, float aspectRatio, float nearPlane, float farPlane, ProjectionType projectionType, Vector2D viewportSize);

		void Update();

		Transform& GetTransform() { return m_transform; }

		Matrix GetViewMatrix();
		Matrix GetProjectionMatrix() const;

		Matrix GetViewProjectionMatrix();

		void SetClearColor(Color color) { m_clearColor = color; }

		void BeginRender(unsigned int clearFlags) const;
		
	private:
		Matrix m_projectionMatrix;
		DirectX::XMMATRIX m_xmMatrix;
		ProjectionType m_projection;
		Transform m_transform;
		Vector2D m_viewportSize;

		Color m_clearColor;

		ID3D11RenderTargetView* m_pRenderTarget;
		ID3D11DepthStencilView* m_pDepthStencil;
		ID3D11Texture2D* m_pDepthBuffer;
		D3D11_VIEWPORT m_viewPort;
	};
}