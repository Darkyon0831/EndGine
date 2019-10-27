#pragma once

#define WIN32_LEAN_AND_MEAN    

#include <windows.h>
#include  "Globals/WString.h"

namespace EG
{
	class EntryPoint
	{
	public:
		int WinEntryPoint(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow);
	private:
		ATOM RegisterWndClass(HINSTANCE hInstance) const;
		int InitInstance(HINSTANCE hInstance, int nCmdShow) const;

		WString m_wndName;
	};
}
