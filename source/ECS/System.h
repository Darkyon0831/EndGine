#pragma once

#include "ISystem.h"

namespace EG
{
	template <typename T>
	class System : public ISystem
	{
	public:
		friend class SystemManager;
		
		System() = default;
		virtual ~System() = default;

	private:
		int m_id;
	};
}