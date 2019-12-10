#pragma once

#include "Graphics/Shader.h"
#include "Components/Mesh.h"

#include "Globals/Singleton.h"
#include "Components/Transform.h"
#include "Graphics/ConstantBuffer.h"

namespace EG
{
	class RenderQueue : public Singleton<RenderQueue>
	{
	public:

		struct FullscreenRender
		{
			ID3D11RenderTargetView* pRenderTargetView;
			D3D11_VIEWPORT viewPort;
			Color clearColor;
			Matrix viewMatrix;
			Matrix projectionMatrix;
			Mesh quad;
		};

		struct FullscreenConstantsVertex
		{
			Matrix worldMatrix;
			Matrix viewMatrix;
			Matrix projectionMatrix;
		};

		struct InstanceData
		{
			Vector3D position;
			Vector3D scale;
		};

		struct FullscreenConstantsPixel
		{
			Color materialColor;
		};
		
		struct VSGeneralVars
		{
			Matrix modelWorldMatrix;
			Matrix cameraViewMatrix;
			Matrix cameraProjectionMatrix;
		};

		struct PSGeneralVars
		{
			Color materialColor;
		};

		struct TextureArray
		{
			ID3D11Texture2D* pTexture2D = nullptr;
			ID3D11ShaderResourceView* pShaderResourceView = nullptr;
		};

		RenderQueue();
		~RenderQueue();

		void InitFullcreenRender();

		void BeginRenderFullscreen() const;
		void EndRenderFullscreen();
	

		void Update();
		void Render();
		
	private:
		ConstantBuffer* m_fullscreenVS;
		ConstantBuffer* m_fullscreenPS;
		
		ConstantBuffer* m_vsGeneral;
		ConstantBuffer* m_psGeneral;
		FullscreenRender m_fullscreenRender;

		TextureArray m_textureArray;
	};
}