#include "Texture.h"
#include <DDSTextureLoader.h>
#include "Globals/Macro.h"
#include <string>
#include "Device.h"
#include "Globals/File/FileSystem.h"

EG::Texture::Texture()
	: m_pTexture(nullptr)
	, m_pShaderResource(__nullptr)
{
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
