#include "EntryPoint.h"

#include  "Containers/WndContainer.h"
#include  "Globals/String.h"
#include  "Settings/WndSettings.h"
#include  "InputHandler.h"
#include  "Globals/Transform.h"
#include "Graphics/Device.h"
#include "Graphics/SwapChain.h"
#include "Tests/SimpeRenderTest.h"
#include "Tests/RenderCubeTest.h"
#include "Graphics/Shader.h"
#include "Graphics/Model.h"
#include "Globals/Clock.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	EG::InputHandler::GetInstance().RegisterInput(wParam, lParam, message);
	
	switch (message) 
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

int EG::EntryPoint::WinEntryPoint(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	// Warning avoid for unused parameters
	(void)hPrevInstance;
	(void)lpCmdLine;

	WndContainer::Initialize();
	WndSettings::Initialize();
	InputHandler::Initialize();
	Clock::Initialize();
	
	m_wndName = L"EndGine";

	// Initialize global strings
	RegisterWndClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	MSG msg;
	Device::Initialize();
	SwapChain::Initialize();
	
	RenderCubeTest renderCubeTest;

	Shader testShader = Shader();
	testShader.Load(String("simpleColor_vertex.hlsl"), String("simpleColor_pixel.hlsl"));

	bool isRunning = true;
	// Main message loop:
	while (isRunning)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (msg.message == WM_QUIT)
			isRunning = false;
		else
		{
			Clock::GetInstance().Update();
			renderCubeTest.Update();
			renderCubeTest.Render();
		}
	}

	return static_cast<int>(msg.wParam);
}

ATOM EG::EntryPoint::RegisterWndClass(const HINSTANCE hInstance) const
{
	WNDCLASSEXW excel;

	excel.cbSize = sizeof(WNDCLASSEX);

	excel.style = CS_HREDRAW | CS_VREDRAW;
	excel.lpfnWndProc = WndProc;
	excel.cbClsExtra = 0;
	excel.cbWndExtra = 0;
	excel.hInstance = hInstance;
	excel.hIcon = LoadIcon(hInstance, nullptr);
	excel.hCursor = LoadCursor(nullptr, IDC_ARROW);
	excel.hbrBackground = CreateSolidBrush(RGB(0, 0, 0));
	excel.lpszMenuName = nullptr;
	excel.lpszClassName = m_wndName.GetString();
	excel.hIconSm = LoadIcon(excel.hInstance, nullptr);

	return RegisterClassExW(&excel);
}

int EG::EntryPoint::InitInstance(HINSTANCE hInstance, int nCmdShow) const
{
	WndContainer::GetInstance().SetHInstance(hInstance);

	HWND hWnd = CreateWindowW(m_wndName.GetString(), m_wndName.GetString(), WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, WndSettings::GetInstance().GetWndWidth(), WndSettings::GetInstance().GetWndHeight(), nullptr, nullptr, hInstance, nullptr);

	WndContainer::GetInstance().SetWindowHandle(hWnd);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}
