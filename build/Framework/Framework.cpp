#include "Core/EntryPoint.h"

#define WIN32_LEAN_AND_MEAN          
#include <windows.h>

EG::EntryPoint entryPoint;

int WINAPI wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	return entryPoint.WinEntryPoint(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
}