#include "RenderQueue.h"

#include "ECS/ComponentManager.h"
#include "Components/CameraComponent.h"

EG::RenderQueue::RenderQueue()
{
	m_vsGeneral = new ConstantBuffer(sizeof(VSGeneralVars));
	m_psGeneral = new ConstantBuffer(sizeof(PSGeneralVars));

	
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

	m_renderQueue.clear();

	SwapChain::GetInstance().Present(1, 0);
}
