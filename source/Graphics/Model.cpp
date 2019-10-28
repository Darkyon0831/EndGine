#include "Model.h"

EG::Model::Model()
{
	D3D11_BUFFER_DESC constantBufferDesc;
	ID3D11Device* pDevice = Device::GetInstance().GetDevice();
	ID3D11Buffer** pVertexConstantBuffer = simpleColorShader.GetVertexConstantBufferPtr();
	ID3D11SamplerState* pSamplerState = simpleColorShader.GetSamplerState();

	//simpleColorShader = Shader();
	simpleColorShader.Load(String("simpleColor_vertex.hlsl"), String("simpleColor_pixel.hlsl"));

	constantBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	constantBufferDesc.ByteWidth = sizeof(ConstantBufferVS);
	constantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	constantBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	constantBufferDesc.MiscFlags = 0;
	constantBufferDesc.StructureByteStride = 0;
	
	pDevice->CreateBuffer(&constantBufferDesc, nullptr, pVertexConstantBuffer);

	int i = 0;
}

EG::Model::~Model()
{
	for (int i = 0; i < m_meshes.size(); i++)
		delete m_meshes.at(i);

	m_meshes.clear();
}

void EG::Model::Update()
{
	m_transform.Update();
}

void EG::Model::Render(Camera& rCurrentCamera)
{
	unsigned int stride;
	unsigned int offset;
	D3D11_MAPPED_SUBRESOURCE vsConstantBufferResource;
	ConstantBufferVS* pConstantBuffer;
	ID3D11DeviceContext* pDeviceContext = Device::GetInstance().GetDeviceContext();
	ID3D11Buffer* pVertexConstantBuffer = simpleColorShader.GetVertexConstantBuffer();
	ID3D11SamplerState* pSamplerState = simpleColorShader.GetSamplerState();

	stride = sizeof(Mesh::Vertex);
	offset = 0;

	pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	pDeviceContext->IASetInputLayout(simpleColorShader.GetInputLayout());
	pDeviceContext->VSSetShader(simpleColorShader.GetVertexShader(), nullptr, 0);
	pDeviceContext->PSSetShader(simpleColorShader.GetPixelShader(), nullptr, 0);
	pDeviceContext->PSSetSamplers(0, 1, &pSamplerState);

	pDeviceContext->Map(pVertexConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &vsConstantBufferResource);
	pConstantBuffer = static_cast<ConstantBufferVS*>(vsConstantBufferResource.pData);
	
	pConstantBuffer->world = m_transform.GetWorldMatrix().Transpose(true);
	pConstantBuffer->view = rCurrentCamera.GetViewMatrix().Transpose(true);
	pConstantBuffer->projection = rCurrentCamera.GetProjectionMatrix().Transpose(true);
	
	pDeviceContext->Unmap(pVertexConstantBuffer, 0);

	pDeviceContext->VSSetConstantBuffers(0, 1, &pVertexConstantBuffer);

	for (unsigned int i = 0; i < m_meshes.size(); i++)
	{
		Mesh* rMesh = m_meshes.at(i);
		ID3D11Buffer* pVertexBuffer = rMesh->GetVertexBuffer();
		ID3D11Buffer* pIndexBuffer = rMesh->GetIndexBuffer();
		
		pDeviceContext->IASetVertexBuffers(0, 1, &pVertexBuffer, &stride, &offset);
		pDeviceContext->IASetIndexBuffer(pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);

		pDeviceContext->DrawIndexed(rMesh->GetIndexCount(), 0, 0);
	}
}
