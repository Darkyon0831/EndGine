#pragma once

#include <vector>
#include "Globals/Vector2D.h"

namespace EG
{
	class Input
	{
	public:

		Input();

		enum KeyState
		{
			KeyDown,
			KeyUp
		};

		struct Mouse
		{
			Vector2D relativMovement;
			Vector2D absoluteMovement;
		};

		struct Key
		{
			char keyCode;
			KeyState state;
		};

		KeyState GetKeyState(char keyCode);
		
	private:
		std::vector<Key> m_frameKeys;
		Key m_defaultKey;
	};
}
