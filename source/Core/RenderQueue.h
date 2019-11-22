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
		
		void AddRenderObject(const RenderObject rRenderObject) { m_renderQueue.push_back(rRenderObject); }

		void Update();
		void Render();
		
	private:
		std::vector<RenderObject> m_renderQueue;

		ConstantBuffer* m_vsGeneral;
		ConstantBuffer* m_psGeneral;

		
	};
}