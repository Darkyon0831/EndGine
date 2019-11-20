#pragma once

#include "IComponent.h"

namespace EG
{
	template <typename T>
	class Component : public ICompoent
	{
	public:
		friend class ComponentManager;

		Component() = default;
		virtual ~Component() = default;
		
	private:
		int m_id;
	};
}
