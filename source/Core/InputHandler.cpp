#include "InputHandler.h"

void EG::InputHandler::RegisterInput(WPARAM wParam, LPARAM lParam, UINT message)
{
	switch (message)
	{
	case WM_KEYDOWN:
		ResetLastInput();
		m_lastInputState.keyCode = wParam;
		m_lastInputState.extendedKey = lParam >> 8 * 24 & 0xff;
		m_lastInputState.repeatCount = ((1 << 16) - 1) & (lParam >> (1 - 1));
		m_lastInputState.keyState = KeyState::KeyDown;
		break;
	case WM_KEYUP:
		ResetLastInput();
		m_lastInputState.keyCode = wParam;
		m_lastInputState.extendedKey = lParam >> 8 * 24 & 0xff;
		m_lastInputState.repeatCount = ((1 << 16) - 1) & (lParam >> (1 - 1));
		m_lastInputState.keyState = KeyState::KeyUp;
		break;
	case WM_LBUTTONDOWN:
		ResetLastInput();
		m_lastInputState.keyState = KeyState::MouseLDown;
		break;
	case WM_LBUTTONUP:
		ResetLastInput();
		m_lastInputState.keyState = KeyState::MouseLUp;
		break;
	case WM_MBUTTONDOWN:
		ResetLastInput();
		m_lastInputState.keyState = KeyState::MouseMDown;
		break;
	case WM_MBUTTONUP:
		ResetLastInput();
		m_lastInputState.keyState = KeyState::MouseMUp;
		break;
	case WM_RBUTTONDOWN:
		ResetLastInput();
		m_lastInputState.keyState = KeyState::MouseRDown;
		break;
	case WM_RBUTTONUP:
		ResetLastInput();
		m_lastInputState.keyState = KeyState::MouseRUp;
		break;
	case WM_MOUSEMOVE:
		ResetLastInput();
		const float lastX = m_lastInputState.absoluteMouse.x;
		const float lastY = m_lastInputState.absoluteMouse.y;
		m_lastInputState.absoluteMouse.x = ((1 << 16) - 1) & (lParam >> (1 - 1));
		m_lastInputState.absoluteMouse.y = ((1 << 16) - 1) & (lParam >> (16 - 1));
		m_lastInputState.relativeMouse.x = m_lastInputState.absoluteMouse.x - lastX;
		m_lastInputState.relativeMouse.y = m_lastInputState.absoluteMouse.y - lastY;
		m_lastInputState.keyState = KeyState::MouseMove;
		break;
	}

	int debug = 0;
}

void EG::InputHandler::ResetLastInput()
{
	m_lastInputState = Input();
}
