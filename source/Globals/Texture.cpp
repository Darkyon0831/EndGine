#include "Texture.h"

EG::Texture::Texture(const String& textureName)
{
	FileSystem::D3D11Texture texture = FileSystem::GetInstance().LoadTexture(textureName);

	m_shaderResourceView = texture.pShaderResourceView;
	m_texture2D = texture.pD311Texture;
}
