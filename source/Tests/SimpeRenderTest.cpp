#include "SimpeRenderTest.h"
#include <ctime>

EG::SimpleRenderTest::SimpleRenderTest()
{
	D3D11_RASTERIZER_DESC rasterDesc;
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	ID3D11Device* pDevice = Device::GetInstance().GetDevice();

	depthStencilDesc.DepthEnable = true;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;
	depthStencilDesc.StencilEnable = true;
	depthStencilDesc.StencilReadMask = 0xFF;
	depthStencilDesc.StencilWriteMask = 0xFF;	
	depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	rasterDesc.FillMode = D3D11_FILL_SOLID;
	rasterDesc.CullMode = D3D11_CULL_NONE;
	rasterDesc.FrontCounterClockwise = false;
	rasterDesc.DepthBias = false;
	rasterDesc.DepthBiasClamp = 0;
	rasterDesc.SlopeScaledDepthBias = 0;
	rasterDesc.DepthClipEnable = true;
	rasterDesc.ScissorEnable = false;
	rasterDesc.MultisampleEnable = false;
	rasterDesc.AntialiasedLineEnable = false;

	EGCHECKHRERROR(pDevice->CreateDepthStencilState(&depthStencilDesc, &m_pDepthStencilState));
	EGCHECKHRERROR(pDevice->CreateRasterizerState(&rasterDesc, &m_rasterState));

	float windowWidth = WndSettings::GetInstance().GetWndWidth();
	float windowHeight = WndSettings::GetInstance().GetWndHeight();

	m_model.GetTransform().scale.Set(0.5f, 0.5f, 0.5f);
	
	m_camera = new Camera(
		45, 
		windowWidth / windowHeight, 
		0.1f, 
		100.0, 
		Camera::ProjectionType::Perspective, 
		Vector2D(windowWidth, windowHeight));

	m_camera->SetClearColor(Color(0.0f, 0.0f, 0.0f));
	m_camera->GetTransform().position.z = -3.0f;

	m_camera->Update();
}

EG::SimpleRenderTest::~SimpleRenderTest()
{
	delete m_camera;
}

void EG::SimpleRenderTest::Render()
{
	ID3D11DeviceContext* pDeviceContext = Device::GetInstance().GetDeviceContext();

	pDeviceContext->RSSetState(m_rasterState);
	m_camera->BeginRender(Camera::ClearFlags::RenderTarget | Camera::ClearFlags::Depth);
	m_model.Render(*m_camera);

	SwapChain::GetInstance().Present(0, 0);
}

void EG::SimpleRenderTest::Update()
{
	m_model.GetTransform().rotation.y += Clock::GetInstance().GetDeltaTime() * 50;
	m_model.Update();
}
