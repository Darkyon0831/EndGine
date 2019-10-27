#include "Device.h"

EG::Device::Device()
	: m_pDevice(nullptr)
	, m_pDeviceContext(nullptr)
{
	IDXGIFactory* pFactory;
	IDXGIAdapter* pAdapter;
	D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_0;

	EGCHECKHRERROR(CreateDXGIFactory(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&pFactory)));
	EGCHECKHRERROR(pFactory->EnumAdapters(0, &pAdapter));

	EGCHECKHRERROR(D3D11CreateDevice(
		nullptr, 
		D3D_DRIVER_TYPE_HARDWARE, 
		nullptr, 
		D3D11_CREATE_DEVICE_DEBUG,
		&featureLevel, 
		1, 
		D3D11_SDK_VERSION, 
		&m_pDevice, 
		nullptr, 
		&m_pDeviceContext));

	pFactory->Release();
	pAdapter->Release();
}

EG::Device::~Device()
{
	m_pDeviceContext->Release();
	m_pDevice->Release();
}
