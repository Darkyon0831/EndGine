#pragma once

#include <windows.h>
#include "Globals/Singleton.h"

namespace EG
{
	class InputHandler : public Singleton<InputHandler>
	{
	public:

		enum KeyState
		{
			KeyDown,
			KeyUp,
			MouseLDown,
			MouseMDown,
			MouseRDown,
			MouseLUp,
			MouseMUp,
			MouseRUp,
			MouseMove
		};

		struct MouseInput
		{
			float x;
			float y;
		};
		
		struct Input
		{
			MouseInput AbsoluteMouse { 0.0f, 0.0f };
			MouseInput RelativMouse;
			KeyState keyState;
			int repeatCount;
			bool extendedKey;
			int keyCode;
		};

		void RegisterInput(WPARAM wParam, LPARAM lParam, UINT message);
		void ResetLastInput();
		
	private:
		Input m_lastInputState = {};
	};
}
