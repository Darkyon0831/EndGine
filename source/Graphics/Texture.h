#pragma once

#include <d3d11.h>
#include <Globals/String.h>

#include "Core/Asset.h"

namespace EG
{
	class Texture : public Asset
	{
	public:
		Texture(bool initializeTexture = false, float width = 0, float height = 0);
		~Texture();

		void Load(const String& textureName);
		void LoadFromMemory(float width, float height, char* buffer, int pitch, int slicePitch = 0);

		ID3D11Texture2D* GetD3D11Texture() const { return m_pTexture; }
		ID3D11ShaderResourceView* GetShaderResourceView() const { return m_pShaderResource; }
		
	private:
		ID3D11Texture2D* m_pTexture;
		ID3D11ShaderResourceView* m_pShaderResource;
	};
}