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
		
		D3D11_TEXTURE2D_DESC texure2DDesc;

		texure2DDesc.Width = width;
		texure2DDesc.Height = height;
		texure2DDesc.MipLevels = 1;
		texure2DDesc.ArraySize = 1;
		texure2DDesc.Format = DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM;
		texure2DDesc.SampleDesc.Count = 1;
		texure2DDesc.SampleDesc.Quality = 0;
		texure2DDesc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
		texure2DDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
		texure2DDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		texure2DDesc.MiscFlags = 0;

		EGCHECKHR(pDevice->CreateTexture2D(&texure2DDesc, nullptr, &m_pTexture));
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
