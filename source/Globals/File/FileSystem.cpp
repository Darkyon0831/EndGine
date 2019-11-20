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

void EG::FileSystem::WriteErrorFile(const String& filename, const String& extension, const String& errorMessage)
{
	String errorPath = GetErrorFileOutputForFile(filename + extension);
	std::ofstream fout;

	fout.open(errorPath.GetString());

	for (int i = 0; i < errorMessage.GetSize(); i++)
	{
		fout << errorMessage[i];
	}

	fout.close();
}
