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
#include <d3d11.h>
#include "Globals/File/FileSystem.h"
#include "Memory/PoolAllocator.h"
#include "Tests/TestEntity.h"
#include "ECS/EntityManager.h"
#include "ECS/ComponentManager.h"
#include "ECS/SystemManager.h"
#include "Tests/TestSystem.h"
#include "Tests/DeltaTimeSystem.h"
#include "Tests/Ecs Test/Cube.h"
#include "Tests/Ecs Test/RenderSystem.h"
#include "Tests/Ecs Test/RotateCubeSystem.h"

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
	FileSystem::Initialize();
	EntityManager::Initialize();
	ComponentManager::Initialize();
	SystemManager::Initialize();

	WndSettings::GetInstance().SetIsVsync(true);

	if (IsDebuggerPresent())
		FileSystem::GetInstance().SetDataLocation("../../game/data/");
	else
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

	InitializeEntities();
	InitializeSystems();
	
	RenderCubeTest renderCubeTest;

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
			//renderCubeTest.Update();
			//renderCubeTest.Render();
			SystemManager::GetInstance().UpdateSystems();

			int debug = 0;
		}
	}

	WndContainer::Uninitialized();
	WndSettings::Uninitialized();
	InputHandler::Uninitialized();
	Clock::Uninitialized();
	SwapChain::Uninitialized();
	Device::Uninitialized();

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
	SystemManager::GetInstance().CreateSystem<RenderSystem>();
	SystemManager::GetInstance().CreateSystem<RotateCubeSystem>();
	SystemManager::GetInstance().InitializeSystems();
}

void EG::EntryPoint::InitializeEntities()
{
	EntityManager::GetInstance().CreateEntity<Cube>();
}
