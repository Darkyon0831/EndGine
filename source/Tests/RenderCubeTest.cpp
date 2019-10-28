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
	rasterDesc.CullMode = D3D11_CULL_BACK;
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

	Mesh::Vertex* vertex = new Mesh::Vertex[8];

	vertex[0].position.Set(-0.5f, 0.5f, -0.5f);
	vertex[0].color = Color(0.0f, 0.0f, 1.0f);
	vertex[0].uv = Vector2D(0.0f, 0.0f);
	vertex[1].position.Set(0.5f, 0.5f, -0.5f);
	vertex[1].color = Color(0.0f, 0.0f, 1.0f);
	vertex[1].uv = Vector2D(1.0f, 0.0f);
	vertex[2].position.Set(0.5f, -0.5f, -0.5f);
	vertex[2].color = Color(0.0f, 0.0f, 1.0f);
	vertex[2].uv = Vector2D(1.0f, 1.0f);
	vertex[3].position.Set(-0.5f, -0.5f, -0.5f);
	vertex[3].color = Color(0.0f, 0.0f, 1.0f);
	vertex[3].uv = Vector2D(0.0f, 1.0f);
	
	vertex[4].position.Set(0.5f, 0.5f, 0.5f);
	vertex[4].color = Color(0.0f, 1.0f, .0f);
	vertex[4].uv = Vector2D(0.0f, 0.0f);
	vertex[5].position.Set(0.5f, -0.5f, 0.5f);
	vertex[5].color = Color(0.0f, 1.0f, 0.0f);
	vertex[5].uv = Vector2D(0.0f, 1.0f);
	vertex[6].position.Set(-0.5f, 0.5f, 0.5f);
	vertex[6].color = Color(0.0f, 1.0f, 0.0f);
	vertex[6].uv = Vector2D(0.0f, 1.0f);
	vertex[7].position.Set(-0.5f, -0.5f, 0.5f);
	vertex[7].color = Color(0.0f, 1.0f, 0.0f);
	vertex[7].uv = Vector2D(1.0f, 1.0f);
	
	int* index = new int[36];

	// Z-planes
	index[0] = 0;
	index[1] = 1;
	index[2] = 3;
	
	index[3] = 1;
	index[4] = 2;
	index[5] = 3;
	
	index[6] = 4;
	index[7] = 6;
	index[8] = 7;
	
	index[9] = 7;
	index[10] = 5;
	index[11] = 4;

	// X-planes
	index[12] = 4;
	index[13] = 1;
	index[14] = 0;
	
	index[15] = 0;
	index[16] = 6;
	index[17] = 4;
	
	index[18] = 5;
	index[19] = 3;
	index[20] = 2;
	
	index[21] = 5;
	index[22] = 7;
	index[23] = 3;

	// Y-planes
	index[24] = 4;
	index[25] = 5;
	index[26] = 2;
	
	index[27] = 2;
	index[28] = 1;
	index[29] = 4;
	
	index[30] = 0;
	index[31] = 7;
	index[32] = 6;
	
	index[33] = 0;
	index[34] = 3;
	index[35] = 7;

	Mesh* quadMesh = new Mesh();
	quadMesh->SetIndexArray(index, 36);
	quadMesh->SetVertexArray(vertex, 8);

	m_model.AddMesh(quadMesh);

	m_camera = new Camera(
		45,
		windowWidth / windowHeight,
		0.1f,
		100.0,
		Camera::ProjectionType::Perspective,
		Vector2D(windowWidth, windowHeight));

	m_camera->GetTransform().rotation.x = 55.0f;
	m_camera->Update();
	
	m_camera->SetClearColor(Color(0.0f, 0.0f, 0.0f));
	m_camera->GetTransform().position.z = -3.5f;
	m_camera->GetTransform().position.y = 3.0f;

	m_camera->Update();

	m_texture = FileSystem::GetInstance().LoadTexture("textures/test2.dds");
}

EG::RenderCubeTest::~RenderCubeTest()
{
	delete m_camera;

	m_pDepthStencilState->Release();
	m_rasterState->Release();
}

void EG::RenderCubeTest::Render()
{
	ID3D11DeviceContext* pDeviceContext = Device::GetInstance().GetDeviceContext();
	
	pDeviceContext->RSSetState(m_rasterState);
	pDeviceContext->PSSetShaderResources(0, 1, &m_texture.pShaderResourceView);
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