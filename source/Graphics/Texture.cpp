#include "Texture.h"
#include <DDSTextureLoader.h>
#include "Globals/Macro.h"
#include <string>
#include "Device.h"
#include "Globals/File/FileSystem.h"

EG::Texture::Texture(const bool initializeTexture, const float width, const float height)
	: Asset(Asset::AssetType::ATexture)
	, m_pTexture(nullptr)
	, m_pShaderResource(nullptr)
{

	if (initializeTexture)
	{
		ID3D11Device* pDevice = Device::GetInstance().GetDevice();
		
		D3D11_TEXTURE2D_DESC texture2DDesc;

		texture2DDesc.Width = width;
		texture2DDesc.Height = height;
		texture2DDesc.MipLevels = 1;
		texture2DDesc.ArraySize = 1;
		texture2DDesc.Format = DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM;
		texture2DDesc.SampleDesc.Count = 1;
		texture2DDesc.SampleDesc.Quality = 0;
		texture2DDesc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
		texture2DDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
		texture2DDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		texture2DDesc.MiscFlags = 0;

		EGCHECKHR(pDevice->CreateTexture2D(&texture2DDesc, nullptr, &m_pTexture));
		EGCHECKHR(pDevice->CreateShaderResourceView(m_pTexture, nullptr, &m_pShaderResource));
	}
	
}

EG::Texture::~Texture()
{
	if (m_pTexture != nullptr)
		m_pTexture->Release();

	if (m_pShaderResource != nullptr)
		m_pShaderResource->Release();
}

void EG::Texture::Load(const String& textureName)
{
	ID3D11Device* pDevice = Device::GetInstance().GetDevice();
	ID3D11Resource* pTextureResource;

	const String fullPath = FileSystem::GetInstance().GetDataLocationForPath(textureName);

	std::wstring vsWS(fullPath.GetSize(), L'#');
	mbstowcs_s(nullptr, &vsWS[0], fullPath.GetSize(), fullPath.GetString(), fullPath.GetSize() - 1);

	EGCHECKHR(DirectX::CreateDDSTextureFromFile(pDevice, vsWS.c_str(), &pTextureResource, &m_pShaderResource));

	pTextureResource->QueryInterface(IID_ID3D11Texture2D, reinterpret_cast<void**>(&m_pTexture));
}

void EG::Texture::LoadFromMemory(float width, float height, char* buffer, int pitch, int slicePitch)
{
	ID3D11Device* pDevice = Device::GetInstance().GetDevice();

	D3D11_TEXTURE2D_DESC texture2DDesc;

	texture2DDesc.Width = width;
	texture2DDesc.Height = height;
	texture2DDesc.MipLevels = 1;
	texture2DDesc.ArraySize = 1;
	texture2DDesc.Format = DXGI_FORMAT::DXGI_FORMAT_R8_UNORM;
	texture2DDesc.SampleDesc.Count = 1;
	texture2DDesc.SampleDesc.Quality = 0;
	texture2DDesc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
	texture2DDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
	texture2DDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	texture2DDesc.MiscFlags = 0;

    D3D11_SUBRESOURCE_DATA resourceData;

    resourceData.pSysMem = buffer;
    resourceData.SysMemPitch = pitch;
    resourceData.SysMemSlicePitch = slicePitch;

	EGCHECKHR(pDevice->CreateTexture2D(&texture2DDesc, &resourceData, &m_pTexture));
	EGCHECKHR(pDevice->CreateShaderResourceView(m_pTexture, nullptr, &m_pShaderResource));
}
