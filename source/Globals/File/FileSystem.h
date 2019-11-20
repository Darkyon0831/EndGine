#pragma once

#include "Globals/Singleton.h"
#include "Globals/String.h"
#include "Graphics/Device.h"

#include <wincodec.h>
#include <d3d11.h>

namespace EG
{
	class FileSystem : public Singleton<FileSystem>
	{
	public:

		struct D3D11Texture
		{
			ID3D11ShaderResourceView* pShaderResourceView = nullptr;
			ID3D11Texture2D* pD311Texture = nullptr;
		};

		struct Convert
		{
			GUID        source;
			GUID        target;
		};
		
		struct FormatConverter
		{
			GUID source;
			DXGI_FORMAT format;
		};

		struct BytesPerPixelConverter
		{
			GUID source;
			size_t bytesPerPixel;
		};

		FileSystem();
		~FileSystem();

		void SetErrorFileOutput(const String& errorFileOutput) { m_errorFileOutput = errorFileOutput; }
		void SetDataLocation(const String& dataLocation) { m_dataLocation = dataLocation; }

		String GetDataLocationForPath(const String& path) const;
		String GetErrorFileOutputForFile(const String& fileName) const;

		void WriteErrorFile(const String& filename, const String& extension, const String& errorMessage);

	private:

		IWICImagingFactory* m_pImageFactory;
		String m_errorFileOutput;
		String m_dataLocation;
	};
}