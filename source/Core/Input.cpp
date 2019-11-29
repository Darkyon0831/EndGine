#include "Input.h"

EG::Input::Input()
{
	m_defaultKey.keyCode = 0;
	m_defaultKey.state = KeyState::KeyDown;
}

EG::Input::KeyState EG::Input::GetKeyState(const char keyCode)
{
	for (auto it = m_frameKeys.begin(); it != m_frameKeys.end(); it++)
	{
		if (it->keyCode == keyCode)
			return it->state;
	}

	return m_defaultKey.state;
}
