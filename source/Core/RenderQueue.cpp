#include "RenderQueue.h"

#include "ECS/ComponentManager.h"
#include "Components/CameraComponent.h"

EG::RenderQueue::RenderQueue()
{
	m_vsGeneral = new ConstantBuffer(sizeof(VSGeneralVars));
	m_psGeneral = new ConstantBuffer(sizeof(PSGeneralVars));

	m_fullscreenVS = new ConstantBuffer(sizeof(FullscreenConstantsVertex));
	m_fullscreenPS = new ConstantBuffer(sizeof(FullscreenConstantsPixel));

	InitFullcreenRender();
}

EG::RenderQueue::~RenderQueue()
{
	delete m_vsGeneral;
	delete m_psGeneral;

	delete m_fullscreenVS;
	delete m_fullscreenPS;
}

void EG::RenderQueue::InitFullcreenRender()
{
	ID3D11Device* pDevice = Device::GetInstance().GetDevice();
	ID3D11Resource* pResource = SwapChain::GetInstance().GetBackBuffer();
	D3D11_RASTERIZER_DESC rasterDesc;
	D3D11_SAMPLER_DESC samplerDesc;
	
	EGCHECKHR(pDevice->CreateRenderTargetView(pResource, nullptr, &m_fullscreenRender.pRenderTargetView));

	const float windowWidth = WndSettings::GetInstance().GetWndWidth();
	const float windowHeight = WndSettings::GetInstance().GetWndHeight();

	m_fullscreenRender.viewPort.Height = windowHeight;
	m_fullscreenRender.viewPort.Width = windowWidth;
	m_fullscreenRender.viewPort.MaxDepth = 1.0f;
	m_fullscreenRender.viewPort.MinDepth = 0.0f;
	m_fullscreenRender.viewPort.TopLeftX = 0.0f;
	m_fullscreenRender.viewPort.TopLeftY = 0.0f;

	m_fullscreenRender.clearColor = Color(0.0f, 0.0f, 0.0f);

	EG::Mesh::Vertex* vertex = new EG::Mesh::Vertex[4];

	vertex[0].position.Set(-0.5f, 0.5f, 0.0f);
	vertex[0].color = EG::Color(1.0f, 1.0f, 1.0f);
	vertex[0].uv = EG::Vector2D(0.0f, 0.0f);
	vertex[1].position.Set(0.5f, 0.5f, 0.0f);
	vertex[1].color = EG::Color(1.0f, 1.0f, 1.0f);
	vertex[1].uv = EG::Vector2D(1.0f, 0.0f);
	vertex[2].position.Set(0.5f, -0.5f, 0.0f);
	vertex[2].color = EG::Color(1.0f, 1.0f, 1.0f);
	vertex[2].uv = EG::Vector2D(1.0f, 1.0f);
	vertex[3].position.Set(-0.5f, -0.5f, 0.0f);
	vertex[3].color = EG::Color(1.0f, 1.0f, 1.0f);
	vertex[3].uv = EG::Vector2D(0.0f, 1.0f);

	int* index = new int[6];

	index[0] = 0;
	index[1] = 1;
	index[2] = 3;

	index[3] = 1;
	index[4] = 2;
	index[5] = 3;

	m_fullscreenRender.quad.SetIndexArray(index, 6);
	m_fullscreenRender.quad.SetVertexArray(vertex, 4);

	m_fullscreenRender.pShader = new Shader();
	m_fullscreenRender.pShader->Load("fullscreen_vertex.hlsl", "fullscreen_pixel.hlsl");
}

void EG::RenderQueue::BeginRenderFullscreen() const
{
	ID3D11DeviceContext* pDeviceContext = Device::GetInstance().GetDeviceContext();

	pDeviceContext->ClearRenderTargetView(m_fullscreenRender.pRenderTargetView, &m_fullscreenRender.clearColor.r);

	pDeviceContext->RSSetViewports(1, &m_fullscreenRender.viewPort);

	pDeviceContext->OMSetRenderTargets(1, &m_fullscreenRender.pRenderTargetView, nullptr);
}

void EG::RenderQueue::Update()
{
	// Todo: Get all meshes with alpha and sort them

	
}

void EG::RenderQueue::Render()
{
	// Todo: Use instancing on all meshes that are the same (ex. cube) to minimize draw calls

	ID3D11DeviceContext* pDeviceContext = Device::GetInstance().GetDeviceContext();
	ID3D11Device* pDevice = Device::GetInstance().GetDevice();

	VSGeneralVars vsGeneralVars;
	PSGeneralVars psGeneralVars;

	ComponentManager::iterator<CameraComponent> cameraIT = ComponentManager::GetInstance().Begin<CameraComponent>();
	const ComponentManager::iterator<CameraComponent> cameraEnd = ComponentManager::GetInstance().End<CameraComponent>();

	for (cameraIT; cameraIT != cameraEnd; cameraIT++)
	{
		cameraIT->BeginRender(CameraComponent::ClearFlags::Depth | CameraComponent::ClearFlags::RenderTarget);
		
		for (unsigned int i = 0; i < m_renderQueue.size(); i++)
		{
			const RenderObject& rRenderObject = m_renderQueue.at(i);
			ID3D11SamplerState* pSampletState = rRenderObject.pShader->GetSamplerState();
			ID3D11Buffer* pVertexConstantBuffer = rRenderObject.pShader->GetVertexConstantBuffer();
			ID3D11Buffer* pPixelConstantBuffer = rRenderObject.pShader->GetPixelConstantBuffer();

			size_t stride = sizeof(Mesh::Vertex);
			size_t offset = 0;

			vsGeneralVars.modelWorldMatrix = rRenderObject.pModel->GetTransform().GetWorldMatrix().Transpose(true);
			vsGeneralVars.cameraViewMatrix = cameraIT->GetViewMatrix().Transpose(true); 
			vsGeneralVars.cameraProjectionMatrix = cameraIT->GetProjectionMatrix().Transpose(true);

			m_vsGeneral->Update(&vsGeneralVars);
			
			ID3D11Buffer* vertexConstantBuffers[2];
			vertexConstantBuffers[0] = m_vsGeneral->GetBuffer();
			vertexConstantBuffers[1] = pVertexConstantBuffer;

			ID3D11Buffer* pixelConstantBuffers[2];
			pixelConstantBuffers[1] = pPixelConstantBuffer;

			pDeviceContext->IASetInputLayout(rRenderObject.pShader->GetInputLayout());
			pDeviceContext->VSSetShader(rRenderObject.pShader->GetVertexShader(), nullptr, 0);
			pDeviceContext->PSSetShader(rRenderObject.pShader->GetPixelShader(), nullptr, 0);
			pDeviceContext->PSSetSamplers(0, 1, &pSampletState);
			pDeviceContext->RSSetState(rRenderObject.pShader->GetRasterizerState());
			pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

			if (rRenderObject.pShader->GetVertexConstantBuffer() != nullptr)
				pDeviceContext->VSSetConstantBuffers(0, 2, vertexConstantBuffers);
			else
				pDeviceContext->VSSetConstantBuffers(0, 1, &vertexConstantBuffers[0]);

			for (unsigned int j = 0; j < rRenderObject.pModel->GetNumMeshes(); j++)
			{
				Mesh* pMesh = rRenderObject.pModel->GetMesh(j);
				Material& rMaterial = pMesh->GetMaterial();
				ID3D11ShaderResourceView* pColormap = rMaterial.GetColormap()->GetShaderResourceView();

				psGeneralVars.materialColor = rMaterial.GetColor();

				m_psGeneral->Update(&psGeneralVars);

				pixelConstantBuffers[0] = m_psGeneral->GetBuffer();

				ID3D11Buffer* pVertexBuffer = pMesh->GetVertexBuffer();
				ID3D11Buffer* pIndexBuffer = pMesh->GetIndexBuffer();

				pDeviceContext->PSSetShaderResources(0, 1, &pColormap);

				if (rRenderObject.pShader->GetPixelConstantBuffer() != nullptr)
					pDeviceContext->PSSetConstantBuffers(0, 2, pixelConstantBuffers);
				else
					pDeviceContext->PSSetConstantBuffers(0, 1, &pixelConstantBuffers[0]);

				pDeviceContext->IASetVertexBuffers(0, 1, &pVertexBuffer, &stride, &offset);
				pDeviceContext->IASetIndexBuffer(pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);

				pDeviceContext->DrawIndexed(pMesh->GetIndexCount(), 0, 0);
			}
		}
	}

	BeginRenderFullscreen();

	cameraIT = ComponentManager::GetInstance().Begin<CameraComponent>();

	for (cameraIT; cameraIT != cameraEnd; cameraIT++)
	{
		Vector2D size = cameraIT->GetSize();
		ID3D11SamplerState* pSamplerState = m_fullscreenRender.pShader->GetSamplerState();
		ID3D11Buffer* pConstVs = m_fullscreenVS->GetBuffer();
		ID3D11Buffer* pConstPs = m_fullscreenPS->GetBuffer();
		ID3D11ShaderResourceView* shaderView = cameraIT->GetTexture()->GetShaderResourceView();

		ID3D11Buffer* pVertexBuffer = m_fullscreenRender.quad.GetVertexBuffer();
		ID3D11Buffer* pIndexBuffer = m_fullscreenRender.quad.GetIndexBuffer();

		size_t stride = sizeof(Mesh::Vertex);
		size_t offset = 0;
		
		m_fullscreenRender.transform.position = Vector3D(-1920.0f / 2.0f + 480.0f / 2.0f, 1080.0f / 2.0f - 270.0f / 2.0f, 0.0f);
		m_fullscreenRender.transform.scale = Vector3D(size.x / 4.0f, size.y / 4.0f, 1.0f);
		m_fullscreenRender.transform.Update();

		m_fullscreenRender.viewMatrix.ApplyViewMatrix(Vector3D::Zero, Vector3D(0.0f, 0.0f, 1.0f));
		m_fullscreenRender.projectionMatrix.ApplyOrthoMatrix(cameraIT->m_viewPort.Width, cameraIT->m_viewPort.Height, 0, 1);
		
		FullscreenConstantsVertex constantVertex;
		constantVertex.worldMatrix = m_fullscreenRender.transform.GetWorldMatrix().Transpose(true);
		constantVertex.viewMatrix = m_fullscreenRender.viewMatrix.Transpose(true);
		constantVertex.projectionMatrix = m_fullscreenRender.projectionMatrix.Transpose(true);
		
		m_fullscreenVS->Update(&constantVertex);

		FullscreenConstantsPixel constantPixel;

		constantPixel.materialColor = Color(1.0f, 1.0f, 1.0f);

		m_fullscreenPS->Update(&constantPixel);

		pDeviceContext->IASetInputLayout(m_fullscreenRender.pShader->GetInputLayout());
		pDeviceContext->VSSetShader(m_fullscreenRender.pShader->GetVertexShader(), nullptr, 0);
		pDeviceContext->PSSetShader(m_fullscreenRender.pShader->GetPixelShader(), nullptr, 0);
		pDeviceContext->PSSetSamplers(0, 1, &pSamplerState);
		pDeviceContext->RSSetState(m_fullscreenRender.pShader->GetRasterizerState());
		pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		pDeviceContext->PSSetShaderResources(0, 1, &shaderView);

		pDeviceContext->VSSetConstantBuffers(0, 1, &pConstVs);
		pDeviceContext->PSSetConstantBuffers(0, 1, &pConstPs);

		pDeviceContext->IASetVertexBuffers(0, 1, &pVertexBuffer, &stride, &offset);
		pDeviceContext->IASetIndexBuffer(pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);

		pDeviceContext->DrawIndexed(m_fullscreenRender.quad.GetIndexCount(), 0, 0);
	}

	m_renderQueue.clear();

	SwapChain::GetInstance().Present(1, 0);
}
