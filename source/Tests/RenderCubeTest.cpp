#include "RenderCubeTest.h"
#include <ctime>

EG::RenderCubeTest::RenderCubeTest()
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

	Mesh::Vertex* vertex = new Mesh::Vertex[24];

	// Z-planes
	vertex[0].position.Set(-0.5f, 0.5f, -0.5f);
	vertex[0].color = Color(0.0f, 0.0f, 1.0f);
	vertex[1].position.Set(0.5f, 0.5f, -0.5f);
	vertex[1].color = Color(0.0f, 1.0f, 0.0f);
	vertex[2].position.Set(0.5f, -0.5f, -0.5f);
	vertex[2].color = Color(0.0f, 1.0f, 0.0f);
	vertex[3].position.Set(-0.5f, -0.5f, -0.5f);
	vertex[3].color = Color(0.0f, 1.0f, 0.0f);
	
	vertex[4].position.Set(-0.5f, 0.5f, 0.5f);
	vertex[4].color = Color(0.0f, 0.0f, 1.0f);
	vertex[5].position.Set(0.5f, 0.5f, 0.5f);
	vertex[5].color = Color(0.0f, 1.0f, 0.0f);
	vertex[6].position.Set(0.5f, -0.5f, 0.5f);
	vertex[6].color = Color(0.0f, 1.0f, 0.0f);
	vertex[7].position.Set(-0.5f, -0.5f, 0.5f);
	vertex[7].color = Color(0.0f, 1.0f, 0.0f);

	// X-planes
	vertex[8].position.Set(-0.5f, 0.5f, -0.5f);
	vertex[8].color = Color(0.0f, 0.0f, 1.0f);
	vertex[9].position.Set(-0.5f, 0.5f, 0.5f);
	vertex[9].color = Color(0.0f, 1.0f, 0.0f);
	vertex[10].position.Set(-0.5f, -0.5f, 0.5f);
	vertex[10].color = Color(0.0f, 1.0f, 0.0f);
	vertex[11].position.Set(-0.5f, -0.5f, -0.5f);
	vertex[11].color = Color(0.0f, 1.0f, 0.0f);
	
	vertex[12].position.Set(0.5f, 0.5f, -0.5f);
	vertex[12].color = Color(0.0f, 0.0f, 1.0f);
	vertex[13].position.Set(0.5f, 0.5f, 0.5f);
	vertex[13].color = Color(0.0f, 1.0f, 0.0f);
	vertex[14].position.Set(0.5f, -0.5f, 0.5f);
	vertex[14].color = Color(0.0f, 1.0f, 0.0f);
	vertex[15].position.Set(0.5f, -0.5f, -0.5f);
	vertex[15].color = Color(0.0f, 1.0f, 0.0f);

	// Y-planes
	vertex[16].position.Set(-0.5f, -0.5f, 0.5f);
	vertex[16].color = Color(0.0f, 0.0f, 1.0f);
	vertex[17].position.Set(0.5f, -0.5f, 0.5f);
	vertex[17].color = Color(0.0f, 1.0f, 0.0f);
	vertex[18].position.Set(0.5f, -0.5f, -0.5f);
	vertex[18].color = Color(0.0f, 1.0f, 0.0f);
	vertex[19].position.Set(-0.5f, -0.5f, -0.5f);
	vertex[19].color = Color(0.0f, 1.0f, 0.0f);
	
	vertex[20].position.Set(-0.5f, 0.5f, 0.5f);
	vertex[20].color = Color(0.0f, 0.0f, 1.0f);
	vertex[21].position.Set(0.5f, 0.5f, 0.5f);
	vertex[21].color = Color(0.0f, 1.0f, 0.0f);
	vertex[22].position.Set(0.5f, 0.5f, -0.5f);
	vertex[22].color = Color(0.0f, 1.0f, 0.0f);
	vertex[23].position.Set(-0.5f, 0.5f, -0.5f);
	vertex[23].color = Color(0.0f, 1.0f, 0.0f);
	
	int* index = new int[36];

	// Z-planes
	index[0] = 0;
	index[1] = 1;
	index[2] = 3;
	index[3] = 1;
	index[4] = 2;
	index[5] = 3;
	index[6] = 4;
	index[7] = 5;
	index[8] = 7;
	index[9] = 5;
	index[10] = 6;
	index[11] = 7;

	// X-planes
	index[12] = 8;
	index[13] = 9;
	index[14] = 11;
	index[15] = 9;
	index[16] = 10;
	index[17] = 11;
	index[18] = 12;
	index[19] = 13;
	index[20] = 15;
	index[21] = 13;
	index[22] = 14;
	index[23] = 15;

	// Y-planes
	index[24] = 16;
	index[25] = 17;
	index[26] = 19;
	index[27] = 17;
	index[28] = 18;
	index[29] = 19;
	index[30] = 20;
	index[31] = 21;
	index[32] = 23;
	index[33] = 21;
	index[34] = 22;
	index[35] = 23;

	Mesh* quadMesh = new Mesh();
	quadMesh->SetIndexArray(index, 36);
	quadMesh->SetVertexArray(vertex, 24);

	m_model.AddMesh(quadMesh);
	m_model.GetTransform().scale.Set(0.5f, 0.5f, 0.5f);

	m_camera = new Camera(
		45,
		windowWidth / windowHeight,
		0.1f,
		100.0,
		Camera::ProjectionType::Perspective,
		Vector2D(windowWidth, windowHeight));

	m_camera->GetTransform().rotation.x = 30.0f;
	m_camera->Update();
	
	m_camera->SetClearColor(Color(0.0f, 0.0f, 0.0f));
	m_camera->GetTransform().position.z = -1.5f;
	m_camera->GetTransform().position.y = 1.0f;

	m_camera->Update();
}

EG::RenderCubeTest::~RenderCubeTest()
{
	delete m_camera;
}

void EG::RenderCubeTest::Render()
{
	ID3D11DeviceContext* pDeviceContext = Device::GetInstance().GetDeviceContext();

	pDeviceContext->RSSetState(m_rasterState);
	m_camera->BeginRender(Camera::ClearFlags::RenderTarget | Camera::ClearFlags::Depth);
	m_model.Render(*m_camera);

	SwapChain::GetInstance().Present(0, 0);
}

void EG::RenderCubeTest::Update()
{
	m_model.GetTransform().rotation.y += Clock::GetInstance().GetDeltaTime() * 50;
	m_model.Update();

	int debug = 0;
}