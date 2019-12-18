#include "Mesh.h"
#include "Globals/Macro.h"
#include "Graphics/Device.h"

EG::Mesh::Mesh()
	: Asset(Asset::AssetType::AMesh)
	, m_vertexArray(nullptr)
	, m_indexArray(nullptr)
	, m_pVertexBuffer(nullptr)
	, m_pIndexBuffer(nullptr)
	, m_vertexCount(0)
	, m_indexCount(0)
{
	
	D3D11_BUFFER_DESC vertexBufferDesc;
	D3D11_BUFFER_DESC indexBufferDesc;
	ID3D11Device* pDevice = Device::GetInstance().GetDevice();

	vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	vertexBufferDesc.ByteWidth = sizeof(Vertex) * 1024;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	indexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	indexBufferDesc.ByteWidth = sizeof(unsigned int) * 2048;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;
	
	EGCHECKHR(pDevice->CreateBuffer(&vertexBufferDesc, nullptr, &m_pVertexBuffer));
	EGCHECKHR(pDevice->CreateBuffer(&indexBufferDesc, nullptr, &m_pIndexBuffer));
}

EG::Mesh::~Mesh()
{
	if (m_pVertexBuffer != nullptr)
		m_pVertexBuffer->Release();

	if (m_pIndexBuffer != nullptr)
		m_pIndexBuffer->Release();

	delete[] m_vertexArray;
	delete[] m_indexArray;
}

void EG::Mesh::SetVertexArray(Vertex* vertexArray, const size_t size)
{
	delete[] m_vertexArray;

	m_vertexArray = vertexArray;
	m_vertexCount = size;

	ID3D11DeviceContext* pDeviceContext = Device::GetInstance().GetDeviceContext();
	D3D11_MAPPED_SUBRESOURCE mappedResource;

	pDeviceContext->Map(m_pVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

	memcpy(mappedResource.pData, m_vertexArray, sizeof(Vertex) * size);

	pDeviceContext->Unmap(m_pVertexBuffer, 0);
}

void EG::Mesh::SetIndexArray(int* indexArray, const size_t size)
{
	delete[] m_indexArray;

	m_indexArray = indexArray;
	m_indexCount = size;

	ID3D11DeviceContext* pDeviceContext = Device::GetInstance().GetDeviceContext();
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	
	pDeviceContext->Map(m_pIndexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

	memcpy(mappedResource.pData, m_indexArray, sizeof(int) * size);

	pDeviceContext->Unmap(m_pIndexBuffer, 0);
}