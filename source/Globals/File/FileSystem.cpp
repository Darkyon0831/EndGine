#include "FileSystem.h"
#include <fstream>

#include <DDSTextureLoader.h>

EG::FileSystem::FileSystem()
	: m_errorFileOutput("")
	, m_dataLocation("")
{
	CoInitialize(nullptr);
	
	HRESULT hr = CoCreateInstance(
		CLSID_WICImagingFactory,
		nullptr,
		CLSCTX_INPROC_SERVER,
		__uuidof(IWICImagingFactory),
		reinterpret_cast<LPVOID*>(&m_pImageFactory)
	);

	int debug = 0;
}

EG::FileSystem::~FileSystem()
{
	CoUninitialize();
	
	m_pImageFactory->Release();
}

EG::String EG::FileSystem::GetDataLocationForPath(const String& path) const
{
	return m_dataLocation + path;
}

EG::String EG::FileSystem::GetErrorFileOutputForFile(const String& fileName) const
{
	return m_errorFileOutput + fileName;
}

void EG::FileSystem::WriteErrorFile(const String& filename, const String& extension)
{
	String errorPath = GetErrorFileOutputForFile(filename + extension);
	std::ofstream fout;
	
	fout.open(errorPath.GetString());

	for (int i = 0; i < errorPath.GetSize(); i++)
	{
		fout << errorPath[i];
	}

	fout.close();
}

EG::FileSystem::D3D11Texture EG::FileSystem::LoadTexture(const String& fromDataPath) const
{
	ID3D11Device* pDevice = Device::GetInstance().GetDevice();
	ID3D11Resource* pTextureResource;
	D3D11Texture texture;
	
	String fullPath = GetDataLocationForPath(fromDataPath);

	std::wstring vsWS(fullPath.GetSize(), L'#');
	mbstowcs_s(nullptr, &vsWS[0], fullPath.GetSize(), fullPath.GetString(), fullPath.GetSize() - 1);
	
	HRESULT hr = DirectX::CreateDDSTextureFromFile(pDevice, vsWS.c_str(), &pTextureResource, &texture.pShaderResourceView);

	pTextureResource->QueryInterface(IID_ID3D11Texture2D, reinterpret_cast<void**>(&texture.pD311Texture));

	return texture;
}
