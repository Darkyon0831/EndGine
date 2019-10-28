#pragma once

#include <windows.h>

#include "Globals/Singleton.h"

namespace EG
{
	class WndContainer : public Singleton<WndContainer>
	{
	public:	
		void SetWindowHandle(HWND& rWindowHandle) { m_windowHandle = rWindowHandle; }
		const HWND& GetWindowHandle() const { return m_windowHandle; }

		void SetHInstance(HINSTANCE& rHInstance) { m_hInstance = rHInstance; }
		const HINSTANCE& GetHInstance() const { return m_hInstance; }

	private:
		HINSTANCE m_hInstance = nullptr;
		HWND m_windowHandle = nullptr;
	};
}
