#pragma once

#include <d3d11.h>

#pragma comment(lib, "D3D11")
#pragma comment(lib, "DXGI")

#include "Globals/Singleton.h"
#include  "Globals/Macro.h"

namespace EG
{
	class Device : public Singleton<Device>
	{
	public:
		Device();
		~Device();

		ID3D11DeviceContext* GetDeviceContext() const { return m_pDeviceContext; }
		ID3D11Device* GetDevice() const { return m_pDevice; }
		
	private:
		ID3D11Device* m_pDevice;
		ID3D11DeviceContext* m_pDeviceContext;
	};
}