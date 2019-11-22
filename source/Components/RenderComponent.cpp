#include "RenderComponent.h"

#include "Core/RenderQueue.h"
#include "Globals/Clock.h"

EG::RenderComponent::RenderComponent()
{

}

EG::RenderComponent::~RenderComponent()
{
	
}

void EG::RenderComponent::PostStart()
{
	// Init constant buffers after the user have defined all variables

	const size_t vertexConstantBufferSize = m_shader.GetTotalSizeOfVariables(EG::Shader::ShaderStage::VS);
	const size_t pixelConstantBufferSize = m_shader.GetTotalSizeOfVariables(EG::Shader::ShaderStage::PS);

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
		EGCHECKHR(pDevice->CreateBuffer(&constantBufferVertexDesc, nullptr, &m_shader.m_pConstantsVertex));

	if (pixelConstantBufferSize > 0)
		EGCHECKHR(pDevice->CreateBuffer(&constantBufferPixelDesc, nullptr, &m_shader.m_pConstantsVertex));

	//m_model.GetTransform().position.z = 5.0f;
}

void EG::RenderComponent::PostUpdate()
{
	// Update constant buffers
	ID3D11DeviceContext* pDeviceContext = Device::GetInstance().GetDeviceContext();

	if (m_shader.m_pConstantsVertex != nullptr)
		UpdateConstantBuffer(Shader::ShaderStage::VS, m_shader.m_pConstantsVertex, pDeviceContext);

	if (m_shader.m_pConstantsPixel != nullptr)
		UpdateConstantBuffer(Shader::ShaderStage::PS, m_shader.m_pConstantsPixel, pDeviceContext);
	
	// Add this render component to the render queue

	RenderQueue::RenderObject renderObject {};
	renderObject.pModel = &m_model;
	renderObject.pShader = &m_shader;
	
	RenderQueue::GetInstance().AddRenderObject(renderObject);
}

void EG::RenderComponent::Update()
{
	float deltaTime = Clock::GetInstance().GetDeltaTime();

	m_model.GetTransform().rotation.y += deltaTime * 25.0f;

	m_model.GetTransform().Update();
}

void EG::RenderComponent::UpdateConstantBuffer(const Shader::ShaderStage shaderStage, ID3D11Buffer* pConstantBuffer, ID3D11DeviceContext* pDeviceContext) const
{
	D3D11_MAPPED_SUBRESOURCE constantBufferResource;
	
	pDeviceContext->Map(pConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &constantBufferResource);
	
	size_t currentStride = 0;
	char* ptrChar = static_cast<char*>(constantBufferResource.pData);

	for (unsigned int i = 0; i < m_shader.m_shaderVariables.size(); i++)
	{
		const Shader::ShaderVariable& shaderVar = m_shader.m_shaderVariables.at(i);

		if (shaderVar.shaderStage == shaderStage)
		{
			memcpy(&ptrChar[currentStride], shaderVar.varPtr, shaderVar.varSize);
			currentStride += shaderVar.varSize;
		}
	}

	pDeviceContext->Unmap(pConstantBuffer, 0);
}
