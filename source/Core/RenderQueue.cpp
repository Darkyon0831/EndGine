#include "RenderQueue.h"

#include "ECS/ComponentManager.h"
#include "Components/CameraComponent.h"
#include "Graphics/SwapChain.h"

#include "Components/RenderComponent.h"

#include "Entities/GameObject.h"

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

	Shader& rShader = m_fullscreenRender.quad.GetMaterial().GetShader();
	rShader.Load("fullscreen_vertex.hlsl", "fullscreen_pixel.hlsl", false);

	D3D11_INPUT_ELEMENT_DESC inputLayout[5]
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{ "TEXCOORD", 1, DXGI_FORMAT_R32G32B32_FLOAT, 1, 0, D3D11_INPUT_PER_INSTANCE_DATA, 1},
		{ "TEXCOORD", 2, DXGI_FORMAT_R32G32B32_FLOAT, 1, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1},
	};

	ID3D11InputLayout* pLayout = rShader.GetInputLayout();
	const void* pVertexShaderBuffer = rShader.GetVertexShaderBuffer();
	const size_t& rVertexShaderBufferSize = rShader.GetVertexShaderBufferSize();
	
	EGCHECKHR(pDevice->CreateInputLayout(inputLayout, 5, pVertexShaderBuffer, rVertexShaderBufferSize, &pLayout));

	rShader.SetInputLayout(pLayout);

	D3D11_TEXTURE2D_DESC texure2DDesc;

	texure2DDesc.Width = windowWidth;
	texure2DDesc.Height = windowHeight;
	texure2DDesc.MipLevels = 1;
	texure2DDesc.ArraySize = 3;
	texure2DDesc.Format = DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM;
	texure2DDesc.SampleDesc.Count = 1;
	texure2DDesc.SampleDesc.Quality = 0;
	texure2DDesc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
	texure2DDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
	texure2DDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	texure2DDesc.MiscFlags = 0;

	EGCHECKHR(pDevice->CreateTexture2D(&texure2DDesc, nullptr, &m_textureArray.pTexture2D));
	EGCHECKHR(pDevice->CreateShaderResourceView(m_textureArray.pTexture2D, nullptr, &m_textureArray.pShaderResourceView));
}

void EG::RenderQueue::BeginRenderFullscreen() const
{
	ID3D11DeviceContext* pDeviceContext = Device::GetInstance().GetDeviceContext();

	pDeviceContext->ClearRenderTargetView(m_fullscreenRender.pRenderTargetView, &m_fullscreenRender.clearColor.r);

	pDeviceContext->RSSetViewports(1, &m_fullscreenRender.viewPort);

	pDeviceContext->OMSetRenderTargets(1, &m_fullscreenRender.pRenderTargetView, nullptr);
}

void EG::RenderQueue::EndRenderFullscreen()
{
	ID3D11DeviceContext* pDeviceContext = Device::GetInstance().GetDeviceContext();

	ID3D11RenderTargetView* nullRTV = nullptr;
	ID3D11ShaderResourceView* nullSRV = nullptr;
	
	pDeviceContext->PSSetShaderResources(0, 1, &nullSRV);
	pDeviceContext->OMSetRenderTargets(1, &nullRTV, nullptr);
}

void EG::RenderQueue::RenderPerspective(
	ID3D11DeviceContext* pDeviceContext,
	ComponentManager::iterator<RenderComponent> renderIT,
	ComponentManager::iterator<CameraComponent> cameraIT) const
{
	VSGeneralVars vsGeneralVars;
	PSGeneralVars psGeneralVars;

	cameraIT->SetDepthStencilState(true);
	
	if ((renderIT->GetGameObject()->Getlayer() & cameraIT->GetRenderLayerMask()) == renderIT->GetGameObject()->Getlayer())
	{
		if (renderIT->GetGameObject()->HaveComponent<Model>())
		{
			Transform* pTransform = renderIT->GetGameObject()->GetComponent<Transform>();

			GameObject* pParent;
			if ((pParent = renderIT->GetGameObject()->GetParent()) != nullptr)
				*pTransform += *pParent->GetTransform();
			
			Model* pModel = renderIT->GetGameObject()->GetComponent<Model>();

			// Loop all meshes

			for (int i = 0; i < pModel->GetTotalMeshes(); i++)
			{
				Mesh* pMesh = pModel->GetMesh(i);
				Shader& rShader = pMesh->GetMaterial().GetShader();
				Material& rMaterial = pMesh->GetMaterial();

				ID3D11SamplerState* pSamplerState = rShader.GetSamplerState();
				ID3D11Buffer* pVertexConstantBuffer = rShader.GetVertexConstantBuffer();
				ID3D11Buffer* pPixelConstantBuffer = rShader.GetPixelConstantBuffer();

				size_t stride = sizeof(Mesh::Vertex);
				size_t offset = 0;

				vsGeneralVars.modelWorldMatrix = pTransform->GetWorldMatrix().Transpose(true);
				vsGeneralVars.cameraViewMatrix = cameraIT->GetViewMatrix(true).Transpose(true);
				vsGeneralVars.cameraProjectionMatrix = cameraIT->GetPerspectiveProjection().Transpose(true);

				m_vsGeneral->Update(&vsGeneralVars);

				ID3D11Buffer* vertexConstantBuffers[2];
				vertexConstantBuffers[0] = m_vsGeneral->GetBuffer();
				vertexConstantBuffers[1] = pVertexConstantBuffer;

				ID3D11Buffer* pixelConstantBuffers[2];
				pixelConstantBuffers[1] = pPixelConstantBuffer;

				pDeviceContext->IASetInputLayout(rShader.GetInputLayout());
				pDeviceContext->VSSetShader(rShader.GetVertexShader(), nullptr, 0);
				pDeviceContext->PSSetShader(rShader.GetPixelShader(), nullptr, 0);
				pDeviceContext->PSSetSamplers(0, 1, &pSamplerState);
				pDeviceContext->RSSetState(rShader.GetRasterizerState());
				pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

				if (rShader.GetVertexConstantBuffer() != nullptr)
					pDeviceContext->VSSetConstantBuffers(0, 2, vertexConstantBuffers);
				else
					pDeviceContext->VSSetConstantBuffers(0, 1, &vertexConstantBuffers[0]);

				ID3D11ShaderResourceView* pColormap = rMaterial.GetColormap()->GetShaderResourceView();

				psGeneralVars.materialColor = rMaterial.GetColor();

				m_psGeneral->Update(&psGeneralVars);

				pixelConstantBuffers[0] = m_psGeneral->GetBuffer();

				ID3D11Buffer* pVertexBuffer = pMesh->GetVertexBuffer();
				ID3D11Buffer* pIndexBuffer = pMesh->GetIndexBuffer();

				pDeviceContext->PSSetShaderResources(0, 1, &pColormap);

				if (rShader.GetPixelConstantBuffer() != nullptr)
					pDeviceContext->PSSetConstantBuffers(0, 2, pixelConstantBuffers);
				else
					pDeviceContext->PSSetConstantBuffers(0, 1, &pixelConstantBuffers[0]);

				pDeviceContext->IASetVertexBuffers(0, 1, &pVertexBuffer, &stride, &offset);
				pDeviceContext->IASetIndexBuffer(pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);

				pDeviceContext->DrawIndexed(pMesh->GetIndexCount(), 0, 0);
			}
		}
	}
}

void EG::RenderQueue::RenderOrthogonal(
	ID3D11DeviceContext* pDeviceContext,
	ComponentManager::iterator<RenderComponent> renderIT,
	ComponentManager::iterator<CameraComponent> cameraIT) const
{
	VSGeneralVars vsGeneralVars;
	PSGeneralVars psGeneralVars;

	cameraIT->SetDepthStencilState(false);
	
	if ((renderIT->GetGameObject()->Getlayer() & cameraIT->GetOrthogonalRenderMask()) == renderIT->GetGameObject()->Getlayer())
	{
		if (renderIT->GetGameObject()->HaveComponent<Model>())
		{
			Transform* pTransform = renderIT->GetGameObject()->GetComponent<Transform>();

			GameObject* pParent;
			if ((pParent = renderIT->GetGameObject()->GetParent()) != nullptr)
				*pTransform += *pParent->GetTransform();
			
			Model* pModel = renderIT->GetGameObject()->GetComponent<Model>();

			for (int i = 0; i < pModel->GetTotalMeshes(); i++)
			{
				Mesh* pMesh = pModel->GetMesh(i);
				Shader& rShader = pMesh->GetMaterial().GetShader();
				Material& rMaterial = pMesh->GetMaterial();

				ID3D11SamplerState* pSamplerState = rShader.GetSamplerState();
				ID3D11Buffer* pVertexConstantBuffer = rShader.GetVertexConstantBuffer();
				ID3D11Buffer* pPixelConstantBuffer = rShader.GetPixelConstantBuffer();

				size_t stride = sizeof(Mesh::Vertex);
				size_t offset = 0;

				vsGeneralVars.modelWorldMatrix = pTransform->GetWorldMatrix().Transpose(true);
				vsGeneralVars.cameraViewMatrix = cameraIT->GetViewMatrix(false).Transpose(true);
				vsGeneralVars.cameraProjectionMatrix = cameraIT->GetOrthogonalProjection().Transpose(true);

				m_vsGeneral->Update(&vsGeneralVars);

				ID3D11Buffer* vertexConstantBuffers[2];
				vertexConstantBuffers[0] = m_vsGeneral->GetBuffer();
				vertexConstantBuffers[1] = pVertexConstantBuffer;

				ID3D11Buffer* pixelConstantBuffers[2];
				pixelConstantBuffers[1] = pPixelConstantBuffer;

				pDeviceContext->IASetInputLayout(rShader.GetInputLayout());
				pDeviceContext->VSSetShader(rShader.GetVertexShader(), nullptr, 0);
				pDeviceContext->PSSetShader(rShader.GetPixelShader(), nullptr, 0);
				pDeviceContext->PSSetSamplers(0, 1, &pSamplerState);
				pDeviceContext->RSSetState(rShader.GetRasterizerState());
				pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

				if (rShader.GetVertexConstantBuffer() != nullptr)
					pDeviceContext->VSSetConstantBuffers(0, 2, vertexConstantBuffers);
				else
					pDeviceContext->VSSetConstantBuffers(0, 1, &vertexConstantBuffers[0]);

				ID3D11ShaderResourceView* pColormap = rMaterial.GetColormap()->GetShaderResourceView();

				psGeneralVars.materialColor = rMaterial.GetColor();

				m_psGeneral->Update(&psGeneralVars);

				pixelConstantBuffers[0] = m_psGeneral->GetBuffer();

				ID3D11Buffer* pVertexBuffer = pMesh->GetVertexBuffer();
				ID3D11Buffer* pIndexBuffer = pMesh->GetIndexBuffer();

				pDeviceContext->PSSetShaderResources(0, 1, &pColormap);

				if (rShader.GetPixelConstantBuffer() != nullptr)
					pDeviceContext->PSSetConstantBuffers(0, 2, pixelConstantBuffers);
				else
					pDeviceContext->PSSetConstantBuffers(0, 1, &pixelConstantBuffers[0]);

				pDeviceContext->IASetVertexBuffers(0, 1, &pVertexBuffer, &stride, &offset);
				pDeviceContext->IASetIndexBuffer(pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);

				pDeviceContext->DrawIndexed(pMesh->GetIndexCount(), 0, 0);
			}
		}
	}
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
	const float& width = WndSettings::GetInstance().GetWndWidth();
	const float& height = WndSettings::GetInstance().GetWndHeight();

	D3D11_BUFFER_DESC instanceBufferDesc;
	D3D11_SUBRESOURCE_DATA instanceData;
	ID3D11Buffer* pInstanceData;

	ComponentManager::iterator<CameraComponent> cameraIT = ComponentManager::GetInstance().Begin<CameraComponent>();
	const ComponentManager::iterator<CameraComponent> cameraEnd = ComponentManager::GetInstance().End<CameraComponent>();

	for (; cameraIT != cameraEnd; cameraIT++)
	{
		cameraIT->BeginRender(CameraComponent::ClearFlags::Depth | CameraComponent::ClearFlags::RenderTarget);

		ComponentManager::iterator<RenderComponent> renderIT = ComponentManager::GetInstance().Begin<RenderComponent>();
		ComponentManager::iterator<RenderComponent> renderEnd = ComponentManager::GetInstance().End<RenderComponent>();

		for (; renderIT != renderEnd; renderIT++)
		{
			RenderPerspective(pDeviceContext, renderIT, cameraIT);
			RenderOrthogonal(pDeviceContext, renderIT, cameraIT);
		}

		cameraIT->EndRender();
	}

	BeginRenderFullscreen();
	Shader& rFullscreenShader = m_fullscreenRender.quad.GetMaterial().GetShader();

	int cameraCount = 0;

	cameraIT = ComponentManager::GetInstance().Begin<CameraComponent>();
	
	for (; cameraIT != cameraEnd; cameraIT++)
		cameraCount++;

	cameraIT = ComponentManager::GetInstance().Begin<CameraComponent>();
	std::vector<InstanceData> vInstanceData;
	vInstanceData.reserve(cameraCount);

	for (; cameraIT != cameraEnd; cameraIT++)
	{
		const Vector2D& rViewportSize = cameraIT->GetViewportSize();
		const Vector2D& rViewportPos = cameraIT->GetViewportPos();

		InstanceData data;
		data.position = Vector3D(rViewportPos.x, rViewportPos.y, 0.0f);
		data.scale = Vector3D(rViewportSize.x, rViewportSize.y, 1.0f);

		vInstanceData.push_back(data);
	}

	instanceBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	instanceBufferDesc.ByteWidth = sizeof(InstanceData) * vInstanceData.size();
	instanceBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	instanceBufferDesc.CPUAccessFlags = 0;
	instanceBufferDesc.MiscFlags = 0;
	instanceBufferDesc.StructureByteStride = 0;

	instanceData.pSysMem = &vInstanceData[0];
	instanceData.SysMemPitch = 0;
	instanceData.SysMemSlicePitch = 0;

	EGCHECKHR(pDevice->CreateBuffer(&instanceBufferDesc, &instanceData, &pInstanceData));

	std::vector<ID3D11ShaderResourceView*> textures;
	textures.reserve(cameraCount);

	cameraIT = ComponentManager::GetInstance().Begin<CameraComponent>();

	m_fullscreenRender.viewMatrix.ApplyViewMatrix(Vector3D::Zero, Vector3D(0.0f, 0.0f, 1.0f));
	m_fullscreenRender.projectionMatrix.ApplyOrthoMatrix(cameraIT->m_viewPort.Width, cameraIT->m_viewPort.Height, 0, 1);
	
	FullscreenConstantsVertex fullscreenConstants;
	fullscreenConstants.worldMatrix = Matrix::identity;
	fullscreenConstants.viewMatrix = m_fullscreenRender.viewMatrix.Transpose(true);
	fullscreenConstants.projectionMatrix = m_fullscreenRender.projectionMatrix.Transpose(true);

	m_fullscreenVS->Update(&fullscreenConstants);

	cameraIT = ComponentManager::GetInstance().Begin<CameraComponent>();
	
	for (; cameraIT != cameraEnd; cameraIT++)
		textures.push_back(cameraIT->GetTexture()->GetShaderResourceView());


	ID3D11Buffer* bufferPointers[2];
	ID3D11SamplerState* pSamplerState = rFullscreenShader.GetSamplerState();
	ID3D11Buffer* pVertexBuffer = m_fullscreenRender.quad.GetVertexBuffer();
	ID3D11Buffer* pIndexBuffer = m_fullscreenRender.quad.GetIndexBuffer();
	ID3D11Buffer* pVSConstantBufferFullscreen = m_fullscreenVS->GetBuffer();

	bufferPointers[0] = pVertexBuffer;
	bufferPointers[1] = pInstanceData;

	size_t strides[2];
	size_t offsets[2];

	strides[0] = sizeof(Mesh::Vertex);
	strides[1] = sizeof(InstanceData);

	offsets[0] = 0;
	offsets[1] = 0;

	ID3D11Resource* pTextureArrayResource;
	m_textureArray.pShaderResourceView->GetResource(&pTextureArrayResource);

	cameraIT = ComponentManager::GetInstance().Begin<CameraComponent>();

	int index = 0;
	for (; cameraIT != cameraEnd; cameraIT++)
	{
		ID3D11Resource* pTextureResource;
		cameraIT->GetTexture()->GetShaderResourceView()->GetResource(&pTextureResource);

		pDeviceContext->CopySubresourceRegion(pTextureArrayResource, index, 0, 0, 0, pTextureResource, 0, nullptr);
		index++;
	}

	pDeviceContext->IASetInputLayout(rFullscreenShader.GetInputLayout());
	pDeviceContext->VSSetShader(rFullscreenShader.GetVertexShader(), nullptr, 0);
	pDeviceContext->PSSetShader(rFullscreenShader.GetPixelShader(), nullptr, 0);
	pDeviceContext->PSSetSamplers(0, 1, &pSamplerState);
	pDeviceContext->RSSetState(rFullscreenShader.GetRasterizerState());
	pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	pDeviceContext->VSSetConstantBuffers(0, 1, &pVSConstantBufferFullscreen);

	pDeviceContext->PSSetShaderResources(0, 1, &m_textureArray.pShaderResourceView);

	pDeviceContext->IASetVertexBuffers(0, 2, bufferPointers, strides, offsets);
	pDeviceContext->IASetIndexBuffer(pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);

	pDeviceContext->DrawIndexedInstanced(m_fullscreenRender.quad.GetIndexCount(), cameraCount, 0, 0, 0);

	EndRenderFullscreen();

	SwapChain::GetInstance().Present(1, 0);
}
