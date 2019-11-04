#include "RenderSystem.h"

#include "ECS/EntityManager.h"
#include "TransformComponent.h"
#include "MeshComponent.h"

#include "Graphics/Device.h"
#include "Graphics/Mesh.h"

RenderSystem::RenderSystem()
{
	D3D11_BUFFER_DESC constantBufferDesc;
	ID3D11Device* pDevice = EG::Device::GetInstance().GetDevice();
	ID3D11Buffer** pVertexConstantBuffer = simpleColorShader.GetVertexConstantBufferPtr();
	
	simpleColorShader.Load(EG::String("simpleColor_vertex.hlsl"), EG::String("simpleColor_pixel.hlsl"));

	constantBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	constantBufferDesc.ByteWidth = sizeof(ConstantBufferVS);
	constantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	constantBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	constantBufferDesc.MiscFlags = 0;
	constantBufferDesc.StructureByteStride = 0;

	D3D11_RASTERIZER_DESC rasterDesc;
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;

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

	pDevice->CreateDepthStencilState(&depthStencilDesc, &m_pDepthStencilState);
	pDevice->CreateRasterizerState(&rasterDesc, &m_rasterState);
	pDevice->CreateBuffer(&constantBufferDesc, nullptr, pVertexConstantBuffer);

	float windowWidth = EG::WndSettings::GetInstance().GetWndWidth();
	float windowHeight = EG::WndSettings::GetInstance().GetWndHeight();
	
	m_camera = new EG::Camera(
		45,
		windowWidth / windowHeight,
		0.1f,
		100.0,
		EG::Camera::ProjectionType::Perspective,
		EG::Vector2D(windowWidth, windowHeight));

	m_camera->GetTransform().rotation.x = 55.0f;
	m_camera->Update();

	m_camera->SetClearColor(EG::Color(0.0f, 0.0f, 0.0f));
	m_camera->GetTransform().position.z = -3.5f;
	m_camera->GetTransform().position.y = 3.0f;

	m_camera->Update();

	m_texture = EG::FileSystem::GetInstance().LoadTexture("textures/test2.dds");
}

void RenderSystem::Render()
{
	// Get components with the Mesh and transform components

	ID3D11DeviceContext* pDeviceContext = EG::Device::GetInstance().GetDeviceContext();
	
	m_camera->BeginRender(EG::Camera::ClearFlags::RenderTarget | EG::Camera::ClearFlags::Depth);

	pDeviceContext->RSSetState(m_rasterState);
	pDeviceContext->PSSetShaderResources(0, 1, &m_texture.pShaderResourceView);
	
	const auto entities = EG::EntityManager::GetInstance().GetEntities();

	for (auto it = entities.begin(); it != entities.end(); it++)
	{
		EG::Entity* pEntity = it->second;
		TransformComponent* transform = static_cast<TransformComponent*>(pEntity->GetComponent<TransformComponent>());
		MeshComponent* mesh = static_cast<MeshComponent*>(pEntity->GetComponent<MeshComponent>());

		if (transform != nullptr && mesh != nullptr)
		{
			EG::Matrix worldMatrix;
			worldMatrix.ScaleRotateTranslate(transform->scale, transform->rotation, transform->position, EG::Matrix::CombineFunc::Replace);

			unsigned int stride;
			unsigned int offset;
			D3D11_MAPPED_SUBRESOURCE vsConstantBufferResource;
			ConstantBufferVS* pConstantBuffer;
			ID3D11Buffer* pVertexConstantBuffer = simpleColorShader.GetVertexConstantBuffer();
			ID3D11SamplerState* pSamplerState = simpleColorShader.GetSamplerState();

			stride = sizeof(EG::Mesh::Vertex);
			offset = 0;

			pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

			pDeviceContext->IASetInputLayout(simpleColorShader.GetInputLayout());
			pDeviceContext->VSSetShader(simpleColorShader.GetVertexShader(), nullptr, 0);
			pDeviceContext->PSSetShader(simpleColorShader.GetPixelShader(), nullptr, 0);
			pDeviceContext->PSSetSamplers(0, 1, &pSamplerState);

			pDeviceContext->Map(pVertexConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &vsConstantBufferResource);
			pConstantBuffer = static_cast<ConstantBufferVS*>(vsConstantBufferResource.pData);

			pConstantBuffer->world = worldMatrix.Transpose(true);
			pConstantBuffer->view = m_camera->GetViewMatrix().Transpose(true);
			pConstantBuffer->projection = m_camera->GetProjectionMatrix().Transpose(true);

			pDeviceContext->Unmap(pVertexConstantBuffer, 0);

			pDeviceContext->VSSetConstantBuffers(0, 1, &pVertexConstantBuffer);
			
			ID3D11Buffer* pVertexBuffer = mesh->GetVertexBuffer();
			ID3D11Buffer* pIndexBuffer = mesh->GetIndexBuffer();

			pDeviceContext->IASetVertexBuffers(0, 1, &pVertexBuffer, &stride, &offset);
			pDeviceContext->IASetIndexBuffer(pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);

			pDeviceContext->DrawIndexed(mesh->GetIndexCount(), 0, 0);
		}
	}

	EG::SwapChain::GetInstance().Present(1, 0);
}
