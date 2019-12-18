#include "EntryPoint.h"

#include  "Containers/WndContainer.h"
#include  "Settings/WndSettings.h"
#include  "InputHandler.h"
#include "Graphics/Device.h"
#include "Graphics/SwapChain.h"
#include "Globals/Clock.h"
#include <d3d11.h>
#include "Globals/File/FileSystem.h"
#include "ECS/EntityManager.h"
#include "ECS/ComponentManager.h"
#include "ECS/SystemManager.h"
#include "Core/RenderQueue.h"

#include "Entities/DefaultCamera.h"
#include "Tests/Entities/TestCube.h"
#include "Tests/Entities/TestCamera.h"
#include "Tests/Entities/TextTest.h"
#include "Tests/Entities/TestQuad.h"

#include <ft2build.h>
#include FT_FREETYPE_H

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	EG::InputHandler::GetInstance().RegisterInput(wParam, lParam, message);

	LPBYTE lpb;
	RAWINPUT* raw;
	
	switch (message) 
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_INPUT:
		unsigned int dwSize;

		GetRawInputData(reinterpret_cast<HRAWINPUT>(lParam), RID_INPUT, nullptr, &dwSize, sizeof(RAWINPUTHEADER));

		lpb = new BYTE[dwSize];
	
		GetRawInputData(reinterpret_cast<HRAWINPUT>(lParam), RID_INPUT, lpb, &dwSize, sizeof(RAWINPUTHEADER));

		raw = reinterpret_cast<RAWINPUT*>(lpb);

		// Handle the input here

		delete[] lpb;
		
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
	FileSystem::Initialize();
	EntityManager::Initialize();
	ComponentManager::Initialize();

	WndSettings::GetInstance().SetIsVsync(false);
	
	FileSystem::GetInstance().SetDataLocation("data/");
	
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

	RenderQueue::Initialize();

	InitializeEntities();
	InitializeSystems();

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

			ComponentManager::GetInstance().UpdateComponents();
			
			RenderQueue::GetInstance().Update();
			RenderQueue::GetInstance().Render();

			int debug = 0;
		}
	}

	WndContainer::Uninitialized();
	WndSettings::Uninitialized();
	InputHandler::Uninitialized();
	Clock::Uninitialized();
	SwapChain::Uninitialized();
	Device::Uninitialized();
	RenderQueue::Uninitialized();

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

void EG::EntryPoint::InitializeSystems()
{
	//SystemManager::GetInstance().InitializeSystems();
}

void EG::EntryPoint::InitializeEntities()
{
	EntityManager::GetInstance().CreateEntity<DefaultCamera>();
    EntityManager::GetInstance().CreateEntity<TestCube>();
	EntityManager::GetInstance().CreateEntity<TestQuad>();
	EntityManager::GetInstance().CreateEntity<TextTest>();
	
	ComponentManager::GetInstance().StartComponents();
}

void EG::EntryPoint::InitializeRawInput()
{
	RAWINPUTDEVICE rid[2];

	rid[0].usUsagePage = 0x01;
	rid[0].usUsage = 0x02;
	rid[0].dwFlags = 0;   
	rid[0].hwndTarget = nullptr;

	rid[1].usUsagePage = 0x01;
	rid[1].usUsage = 0x06;
	rid[1].dwFlags = 0;   
	rid[1].hwndTarget = nullptr;

	RegisterRawInputDevices(rid, 2, sizeof(RAWINPUTDEVICE));
}
