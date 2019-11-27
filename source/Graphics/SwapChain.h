#pragma once

#include <d3d11.h>
#include <dxgi1_2.h>

#include "Globals/Singleton.h"
#include "Globals/Macro.h"
#include "Settings/WndSettings.h"
#include "Containers/WndContainer.h"
#include "Graphics/Device.h"

namespace EG
{
	class SwapChain : public Singleton<SwapChain>
	{
	public:
		SwapChain();
		~SwapChain();

		ID3D11Texture2D* GetBackBuffer() const;

		void Present(UINT syncInterval, UINT flags) const;
		
	private:
		IDXGISwapChain* m_pSwapChain;
	};
}