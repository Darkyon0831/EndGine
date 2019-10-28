#include "Camera.h"

EG::Camera::Camera(float fov, float aspectRatio, float nearPlane, float farPlane, ProjectionType projectionType, Vector2D viewportSize)
	: m_clearColor(0.0f, 0.0f, 0.0f)
{
	D3D11_TEXTURE2D_DESC depthBufferDesc;
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
	float windowWidth = WndSettings::GetInstance().GetWndWidth();
	float windowHeight = WndSettings::GetInstance().GetWndHeight();
	
	if (projectionType == ProjectionType::Perspective)
		m_projectionMatrix.ApplyPerspectiveMatrix(aspectRatio, fov, nearPlane, farPlane);
	else if (projectionType == ProjectionType::Orthogonal)
		m_projectionMatrix.ApplyOrthoMatrix(windowWidth, windowHeight, nearPlane, farPlane);

	m_projection = projectionType;
	m_viewportSize = viewportSize;

	ID3D11Device* pDevice = Device::GetInstance().GetDevice();
	ID3D11Texture2D* pTexture = SwapChain::GetInstance().GetBackBuffer();
	EGCHECKHRERROR(pDevice->CreateRenderTargetView(pTexture, NULL, &m_pRenderTarget));
	pTexture->Release();

	depthBufferDesc.Width = viewportSize.x;
	depthBufferDesc.Height = viewportSize.y;
	depthBufferDesc.MipLevels = 1;
	depthBufferDesc.ArraySize = 1;
	depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthBufferDesc.SampleDesc.Count = 1;
	depthBufferDesc.SampleDesc.Quality = 0;
	depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthBufferDesc.CPUAccessFlags = 0;
	depthBufferDesc.MiscFlags = 0;

	EGCHECKHRERROR(pDevice->CreateTexture2D(&depthBufferDesc, nullptr, &m_pDepthBuffer));

	depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Texture2D.MipSlice = 0;
	depthStencilViewDesc.Flags = 0;
	
	EGCHECKHRERROR(pDevice->CreateDepthStencilView(m_pDepthBuffer, &depthStencilViewDesc, &m_pDepthStencil));
}

void EG::Camera::Update()
{
	m_viewPort.TopLeftX = m_transform.position.x;
	m_viewPort.TopLeftY = m_transform.position.y;
	m_viewPort.Width = m_viewportSize.x;
	m_viewPort.Height = m_viewportSize.y;
	m_viewPort.MinDepth = 0;
	m_viewPort.MaxDepth = 1;

	m_transform.Update();
}

EG::Matrix EG::Camera::GetViewMatrix()
{
	Matrix viewMatrix = Matrix::identity;

	viewMatrix.ApplyViewMatrix(m_transform.position, m_transform.GetForward());

	return viewMatrix;
}

EG::Matrix EG::Camera::GetProjectionMatrix() const
{
	return m_projectionMatrix;
}

EG::Matrix EG::Camera::GetViewProjectionMatrix()
{
	Matrix viewMatrix = Matrix::identity;
	Vector3D cameraForward = m_transform.GetForward();
	
	viewMatrix.ApplyViewMatrix(m_transform.position, m_transform.position + cameraForward);

	return viewMatrix * m_projectionMatrix;
}

void EG::Camera::BeginRender(unsigned int clearFlags) const
{
	// Clear buffers

	ID3D11DeviceContext* pDeviceContext = Device::GetInstance().GetDeviceContext();
	
	bool clearRenderTarget = clearFlags >> 0 & 0x01;
	bool clearStencil = clearFlags >> 1 & 0x01;
	bool clearDepth = clearFlags >> 2 & 0x01;

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
