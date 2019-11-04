#pragma once

namespace EG
{
	template <typename T>
	class Component
	{
	public:
		friend class ComponentManager;

		Component() = default;
		~Component() = default;
		
	private:
		int m_id;
	};
}
