#pragma once

#include <d3d11.h>
#include <Globals/String.h>

namespace EG
{
	class Texture
	{
	public:
		Texture();
		~Texture();

		void Load(const String& textureName);

		ID3D11Texture2D* GetD3D11Texture() const { return m_pTexture; }
		ID3D11ShaderResourceView* GetShaderResourceView() const { return m_pShaderResource; }
		
	private:
		ID3D11Texture2D* m_pTexture;
		ID3D11ShaderResourceView* m_pShaderResource;
	};
}