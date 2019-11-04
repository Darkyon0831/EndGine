#pragma once

#include "File/FileSystem.h"
#include "Globals/String.h"

namespace EG
{
	class Texture
	{
	public:
		Texture(const String& textureName);
		
	private:
		ID3D11ShaderResourceView* m_shaderResourceView;
		ID3D11Texture2D* m_texture2D;
	};
}