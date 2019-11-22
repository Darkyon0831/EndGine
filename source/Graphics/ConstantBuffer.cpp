#include "ConstantBuffer.h"

#include "Globals/Macro.h"
#include "Graphics/Device.h"

EG::ConstantBuffer::ConstantBuffer(const size_t size)
	: m_pBuffer(nullptr)
	, m_size(size)
{
	ID3D11Device* pDevice = Device::GetInstance().GetDevice();
	
	D3D11_BUFFER_DESC bufferDesc;
	bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	bufferDesc.ByteWidth = size;
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	EGCHECKHR(pDevice->CreateBuffer(&bufferDesc, nullptr, &m_pBuffer));
}

EG::ConstantBuffer::~ConstantBuffer()
{
	if (m_pBuffer)
		m_pBuffer->Release();
}

void EG::ConstantBuffer::Update(void* pMem) const
{
	ID3D11DeviceContext* pDeviceContext = Device::GetInstance().GetDeviceContext();
	D3D11_MAPPED_SUBRESOURCE bufferResource;
	
	EGCHECKHR(pDeviceContext->Map(m_pBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &bufferResource));

	memcpy(bufferResource.pData, pMem, m_size);

	pDeviceContext->Unmap(m_pBuffer, 0);
}
