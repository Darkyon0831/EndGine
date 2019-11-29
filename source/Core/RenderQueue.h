#pragma once

#include "Graphics/Shader.h"
#include "Graphics/Model.h"

#include "Globals/Singleton.h"
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
			Transform transform;
			Shader* pShader;
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
			Matrix worldMatrix;
			Matrix viewMatrix;
			Matrix projectionMatrix;
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
		
		struct RenderObject
		{
			Shader* pShader;
			Model* pModel;
		};

		RenderQueue();
		~RenderQueue();

		void InitFullcreenRender();

		void BeginRenderFullscreen() const;
		void EndRenderFullscreen();
		
		void AddRenderObject(const RenderObject rRenderObject) { m_renderQueue.push_back(rRenderObject); }

		void Update();
		void Render();
		
	private:
		std::vector<RenderObject> m_renderQueue;

		ConstantBuffer* m_fullscreenVS;
		ConstantBuffer* m_fullscreenPS;
		
		ConstantBuffer* m_vsGeneral;
		ConstantBuffer* m_psGeneral;
		FullscreenRender m_fullscreenRender;
	};
}