#pragma once

#include "ECS/System.h"
#include "ECS/SystemManager.h"
#include "Graphics/Shader.h"
#include "Globals/Camera.h"
#include "Globals/File/FileSystem.h"

class RenderSystem : public EG::System<RenderSystem>
{
public:

	struct ConstantBufferVS
	{
		EG::Matrix world;
		EG::Matrix view;
		EG::Matrix projection;
	};
	
	RenderSystem();

private:
	ID3D11DepthStencilState* m_pDepthStencilState;
	ID3D11RasterizerState* m_rasterState;
	EG::Camera* m_camera;
	EG::Shader simpleColorShader;

	EG::FileSystem::D3D11Texture m_texture;
};
