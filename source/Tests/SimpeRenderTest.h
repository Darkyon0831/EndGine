#pragma once

#include <d3d11.h>
#include "Globals/Camera.h"
#include "Settings/WndSettings.h"
#include "Graphics/Device.h"
#include "Graphics/SwapChain.h"
#include "Globals/Macro.h"
#include "Graphics/Model.h"
#include "Globals/Clock.h"

namespace EG
{
	class SimpleRenderTest
	{
	public:
		SimpleRenderTest();
		~SimpleRenderTest();

		void Render();
		void Update();

	private:
		ID3D11DepthStencilState* m_pDepthStencilState;
		ID3D11RasterizerState* m_rasterState;
		Camera* m_camera;
		Model m_model;

		float deltaTime;
		
	};	
}