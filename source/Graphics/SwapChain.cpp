#include "SwapChain.h"

EG::SwapChain::SwapChain()
	: m_pSwapChain(nullptr)
{
	IDXGIFactory* pFactory;
	IDXGIAdapter* pAdapter;
	IDXGIOutput* pAdapterOutput;
	DXGI_SWAP_CHAIN_DESC swapChainDesc{};
	DXGI_MODE_DESC* pDisplayModeList;
	DXGI_ADAPTER_DESC adapterDesc;
	unsigned int numModes, i, numerator = 0, denominator = 0;
	float screenWidth = WndSettings::GetInstance().GetWndWidth();
	float screenHeight = WndSettings::GetInstance().GetWndHeight();
	bool isVsync = WndSettings::GetInstance().GetIsVsync();
	bool isFullscreen = WndSettings::GetInstance().GetIsFullscreen();
	const HWND& windowHandle = WndContainer::GetInstance().GetWindowHandle();
	ID3D11Device* pDevice = Device::GetInstance().GetDevice();
	IDXGIDevice* pDxgiDevice;
	
	EGCHECKHR(pDevice->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&pDxgiDevice)));
	EGCHECKHR(pDxgiDevice->GetAdapter(&pAdapter));
	EGCHECKHR(pAdapter->GetParent(__uuidof(IDXGIFactory2), reinterpret_cast<void**>(&pFactory)));
	EGCHECKHR(pAdapter->EnumOutputs(0, &pAdapterOutput));
	EGCHECKHR(pAdapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, nullptr));

	pDisplayModeList = new DXGI_MODE_DESC[numModes];

	EGCHECKHR(pAdapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, pDisplayModeList));

	for (i = 0; i < numModes; i++)
	{
		if (pDisplayModeList[i].Width == static_cast<unsigned int>(screenWidth))
		{
			if (pDisplayModeList[i].Height == static_cast<unsigned int>(screenHeight))
			{
				numerator = pDisplayModeList[i].RefreshRate.Numerator;
				denominator = pDisplayModeList[i].RefreshRate.Denominator;
			}
		}
	}

	if (isVsync)
	{
		swapChainDesc.BufferDesc.RefreshRate.Numerator = numerator;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = denominator;
	}
	else
	{
		swapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	}

	EGCHECKHR(pAdapter->GetDesc(&adapterDesc));
	delete[] pDisplayModeList;
	pAdapterOutput->Release();
	pAdapter->Release();

	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Width = screenWidth;
	swapChainDesc.BufferDesc.Height = screenHeight;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = windowHandle;

	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;

	if (isFullscreen)
		swapChainDesc.Windowed = false;
	else
		swapChainDesc.Windowed = true;

	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapChainDesc.Flags = 0;

	EGCHECKHR(pFactory->CreateSwapChain(pDxgiDevice, &swapChainDesc, &m_pSwapChain));

	pFactory->Release();
	pDxgiDevice->Release();
}

EG::SwapChain::~SwapChain()
{
	m_pSwapChain->Release();
}

ID3D11Texture2D* EG::SwapChain::GetBackBuffer() const
{
	ID3D11Texture2D* ptr = nullptr;
	
	EGCHECKHR(m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<LPVOID*>(&ptr)));

	return ptr;
}

void EG::SwapChain::Present(UINT syncInterval, UINT flags)
{
	EGCHECKHR(m_pSwapChain->Present(syncInterval, flags));
}
