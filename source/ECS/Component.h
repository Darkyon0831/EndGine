#pragma once

#include "IComponent.h"

namespace EG
{
	template <typename T>
	class Component : public IComponent
	{
	public:
		friend class ComponentManager;

		Component() : m_id(0) {}
		virtual ~Component() = default;

		int GetID() const { return m_id; }
		
	private:
		int m_id;
	};
}
