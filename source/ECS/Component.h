#pragma once

#include "IComponent.h"

namespace EG
{
	template <typename T>
	class Component : public IComponent
	{
	public:
		friend class ComponentManager;

		Component() : m_id(0), m_entityID(-1) {}
		virtual ~Component() = default;
		
	protected:
		int m_id;
		int m_entityID;
	};
}
