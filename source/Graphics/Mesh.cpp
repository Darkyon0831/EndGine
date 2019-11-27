#include "Mesh.h"

EG::Mesh::Mesh()
	: Asset(Asset::AssetType::Mesh)
	, m_vertexArray(nullptr)
	, m_indexArray(nullptr)
	, m_pVertexBuffer(nullptr)
	, m_pIndexBuffer(nullptr)
	, m_vertexCount(0)
	, m_indexCount(0)
{

}

EG::Mesh::~Mesh()
{
	if (m_pVertexBuffer != nullptr)
		m_pVertexBuffer->Release();

	if (m_pIndexBuffer != nullptr)
		m_pIndexBuffer->Release();

	if (m_vertexArray != nullptr)
		delete[] m_vertexArray;

	if (m_indexArray != nullptr)
		delete[] m_indexArray;
}

void EG::Mesh::SetVertexArray(Vertex* vertexArray, size_t size)
{
	if (m_vertexArray != nullptr)
		delete[] m_vertexArray;
	
	if (m_pVertexBuffer != nullptr)
		m_pVertexBuffer->Release();
	
	m_vertexArray = vertexArray;
	m_vertexCount = size;
	
	D3D11_BUFFER_DESC vertexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData;
	ID3D11Device* pDevice = Device::GetInstance().GetDevice();
	
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(Vertex) * size;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	vertexData.pSysMem = m_vertexArray;
	vertexData.SysMemSlicePitch = 0;
	vertexData.SysMemPitch = 0;

	HRESULT result = pDevice->CreateBuffer(&vertexBufferDesc, &vertexData, &m_pVertexBuffer);

	int debug = 0;
}

void EG::Mesh::SetIndexArray(int* indexArray, size_t size)
{
	if (m_indexArray != nullptr)
		delete[] m_indexArray;
	
	if (m_pIndexBuffer != nullptr)
		m_pIndexBuffer->Release();

	m_indexArray = indexArray;
	m_indexCount = size;

	D3D11_BUFFER_DESC indexBufferDesc;
	D3D11_SUBRESOURCE_DATA indexData;
	ID3D11Device* pDevice = Device::GetInstance().GetDevice();

	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(Vertex) * size;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	indexData.pSysMem = m_indexArray;
	indexData.SysMemSlicePitch = 0;
	indexData.SysMemPitch = 0;

	pDevice->CreateBuffer(&indexBufferDesc, &indexData, &m_pIndexBuffer);
}
