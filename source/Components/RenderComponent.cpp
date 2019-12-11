#include "RenderComponent.h"

#include "Core/RenderQueue.h"
#include "Globals/Clock.h"

#include "Entities/GameObject.h"

EG::RenderComponent::RenderComponent()
{
	
}

EG::RenderComponent::~RenderComponent()
{
	
}

void EG::RenderComponent::PostStart()
{
	// Init constant buffers after the user have defined all variables

	Model* pModel = GetGameObject()->GetComponent<Model>();

	for (int i = 0; i< pModel->GetTotalMeshes(); i++)
	{
		Shader& rShader = pModel->GetMesh(i)->GetMaterial().GetShader();

		const size_t vertexConstantBufferSize = rShader.GetTotalSizeOfVariables(EG::Shader::ShaderStage::VS);
		const size_t pixelConstantBufferSize = rShader.GetTotalSizeOfVariables(EG::Shader::ShaderStage::PS);

		ID3D11Device* pDevice = Device::GetInstance().GetDevice();

		D3D11_BUFFER_DESC constantBufferVertexDesc;
		D3D11_BUFFER_DESC constantBufferPixelDesc;

		constantBufferVertexDesc.Usage = D3D11_USAGE_DYNAMIC;
		constantBufferVertexDesc.ByteWidth = vertexConstantBufferSize;
		constantBufferVertexDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		constantBufferVertexDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		constantBufferVertexDesc.MiscFlags = 0;
		constantBufferVertexDesc.StructureByteStride = 0;

		constantBufferPixelDesc.Usage = D3D11_USAGE_DYNAMIC;
		constantBufferPixelDesc.ByteWidth = pixelConstantBufferSize;
		constantBufferPixelDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		constantBufferPixelDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		constantBufferPixelDesc.MiscFlags = 0;
		constantBufferPixelDesc.StructureByteStride = 0;

		if (vertexConstantBufferSize > 0)
			EGCHECKHR(pDevice->CreateBuffer(&constantBufferVertexDesc, nullptr, &rShader.m_pConstantsVertex));

		if (pixelConstantBufferSize > 0)
			EGCHECKHR(pDevice->CreateBuffer(&constantBufferPixelDesc, nullptr, &rShader.m_pConstantsVertex));
	}
}

void EG::RenderComponent::PostUpdate()
{
	Model* pModel = GetGameObject()->GetComponent<Model>();

	for (int i = 0; i < pModel->GetTotalMeshes(); i++)
	{
		Shader& rShader = pModel->GetMesh(i)->GetMaterial().GetShader();

		// Update constant buffers
		ID3D11DeviceContext* pDeviceContext = Device::GetInstance().GetDeviceContext();

		if (rShader.m_pConstantsVertex != nullptr)
			UpdateConstantBuffer(rShader, Shader::ShaderStage::VS, rShader.m_pConstantsVertex, pDeviceContext);

		if (rShader.m_pConstantsPixel != nullptr)
			UpdateConstantBuffer(rShader, Shader::ShaderStage::PS, rShader.m_pConstantsPixel, pDeviceContext);
	}
}

void EG::RenderComponent::UpdateConstantBuffer(Shader& rShader, const Shader::ShaderStage shaderStage, ID3D11Buffer* pConstantBuffer, ID3D11DeviceContext* pDeviceContext) const
{
	D3D11_MAPPED_SUBRESOURCE constantBufferResource;
	
	pDeviceContext->Map(pConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &constantBufferResource);
	
	size_t currentStride = 0;
	char* ptrChar = static_cast<char*>(constantBufferResource.pData);

	for (unsigned int i = 0; i < rShader.m_shaderVariables.size(); i++)
	{
		const Shader::ShaderVariable& shaderVar = rShader.m_shaderVariables.at(i);

		if (shaderVar.shaderStage == shaderStage)
		{
			memcpy(&ptrChar[currentStride], shaderVar.varPtr, shaderVar.varSize);
			currentStride += shaderVar.varSize;
		}
	}

	pDeviceContext->Unmap(pConstantBuffer, 0);
}
