#include "CameraComponent.h"
#include "Globals/Macro.h"
#include "Graphics/SwapChain.h"

#include "Entities/GameObject.h"

EG::CameraComponent::CameraComponent(
	const float fov, 
	const float aspectRatio, 
	const float nearPlane, 
	const float farPlane, 
	const ProjectionType projectionType, 
	const Vector2D viewportSize,
	const Vector2D viewportPos)
{
	D3D11_TEXTURE2D_DESC depthBufferDesc;
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;

	const float& rWindowWidth = WndSettings::GetInstance().GetWndWidth();
	const float& rWindowHeight = WndSettings::GetInstance().GetWndHeight();

	m_projection = projectionType;

	m_viewPort.TopLeftX = 0.0f;
	m_viewPort.TopLeftY = 0.0f;
	m_viewPort.Width = rWindowWidth;
	m_viewPort.Height = rWindowHeight;
	m_viewPort.MinDepth = 0.0f;
	m_viewPort.MaxDepth = 1.0f;

	m_viewportSize = viewportSize;
	m_viewportPos = viewportPos;

	m_texture = new Texture(true, rWindowWidth, rWindowHeight);

	m_fov = fov;
	m_aspectRatio = aspectRatio;
	m_nearPlane = nearPlane;
	m_farPlane = farPlane;

	ID3D11Device* pDevice = Device::GetInstance().GetDevice();
	ID3D11Texture2D* pTexture = m_texture->GetD3D11Texture();
	EGCHECKHR(pDevice->CreateRenderTargetView(pTexture, NULL, &m_pRenderTarget));
	pTexture->Release();

	depthBufferDesc.Width = rWindowWidth;
	depthBufferDesc.Height = rWindowHeight;
	depthBufferDesc.MipLevels = 1;
	depthBufferDesc.ArraySize = 1;
	depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthBufferDesc.SampleDesc.Count = 1;
	depthBufferDesc.SampleDesc.Quality = 0;
	depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthBufferDesc.CPUAccessFlags = 0;
	depthBufferDesc.MiscFlags = 0;

	EGCHECKHR(pDevice->CreateTexture2D(&depthBufferDesc, nullptr, &m_pDepthBuffer));

	depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Texture2D.MipSlice = 0;
	depthStencilViewDesc.Flags = 0;

	EGCHECKHR(pDevice->CreateDepthStencilView(m_pDepthBuffer, &depthStencilViewDesc, &m_pDepthStencil));
	
	//m_frustum.Update(nearPlane, farPlane, m_transform, aspectRatio, fov);
}

EG::CameraComponent::~CameraComponent()
{
	delete m_texture;
}

void EG::CameraComponent::Update()
{
	//m_frustum.Update(m_nearPlane, m_farPlane, m_transform, m_aspectRatio, m_fov);;
}

EG::Matrix EG::CameraComponent::GetViewMatrix() const
{
	Matrix viewMatrix = Matrix::identity;
	
	if (GetGameObject()->HaveComponent<Transform>())
	{
		Transform* transform = GetGameObject()->GetComponent<Transform>();
		
		viewMatrix.ApplyViewMatrix(transform->position, transform->position + transform->GetForward());
	}

	return viewMatrix;
}

EG::Matrix EG::CameraComponent::GetProjectionMatrix() const
{
	Matrix projectionMatrix = Matrix::identity;
	
	if (m_projection == ProjectionType::Perspective)
		projectionMatrix.ApplyPerspectiveMatrix(m_aspectRatio, m_fov, m_nearPlane, m_farPlane);
	else if (m_projection == ProjectionType::Orthogonal)
		projectionMatrix.ApplyOrthoMatrix(m_viewPort.Width, m_viewPort.Height, m_nearPlane, m_farPlane);

	return projectionMatrix;
}

EG::Matrix EG::CameraComponent::GetViewProjectionMatrix() const
{
	Matrix projectionMatrix = GetProjectionMatrix();
	Matrix viewMatrix = GetViewMatrix();

	return viewMatrix * projectionMatrix;
}

void EG::CameraComponent::BeginRender(const unsigned int clearFlags) const
{
	ID3D11DeviceContext* pDeviceContext = Device::GetInstance().GetDeviceContext();

	const bool clearRenderTarget = clearFlags >> 0 & 0x01;
	const bool clearStencil = clearFlags >> 1 & 0x01;
	const bool clearDepth = clearFlags >> 2 & 0x01;

	UINT clearStencilViewFlags = 0;

	if (clearStencil)
		clearStencilViewFlags |= D3D11_CLEAR_FLAG::D3D11_CLEAR_STENCIL;

	if (clearDepth)
		clearStencilViewFlags |= D3D11_CLEAR_FLAG::D3D11_CLEAR_DEPTH;

	if (clearRenderTarget)
		pDeviceContext->ClearRenderTargetView(m_pRenderTarget, &m_clearColor.r);

	pDeviceContext->RSSetViewports(1, &m_viewPort);
	pDeviceContext->ClearDepthStencilView(m_pDepthStencil, clearStencilViewFlags, 1.0f, 0.0f);

	pDeviceContext->OMSetRenderTargets(1, &m_pRenderTarget, m_pDepthStencil);
}

void EG::CameraComponent::EndRender()
{
	ID3D11DeviceContext* pDeviceContext = Device::GetInstance().GetDeviceContext();
	
	ID3D11RenderTargetView* nullRTV = nullptr;
	
	pDeviceContext->OMSetRenderTargets(1, &nullRTV, nullptr);
}
