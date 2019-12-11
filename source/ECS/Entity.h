#pragma once

#include "ComponentManager.h"

namespace EG
{
	class Entity
	{
	public:
		friend class EntityManager;
		
		Entity() = default;
		virtual ~Entity() = default;

		template <typename ComponentT>
		ComponentT* GetComponent();

		template <typename ComponentT, typename... Args>
		ComponentT* CreateComponent(Args... args);

		template <typename ComponentT>
		bool HaveComponent();

		template <typename ComponentT>
		void RemoveComponent();
		
	protected:
		int m_id;
	};

	template <typename ComponentT>
	ComponentT* Entity::GetComponent()
	{
		return ComponentManager::GetInstance().GetComponent<ComponentT>(m_id);
	}

	template <typename ComponentT, typename... Args>
	ComponentT* Entity::CreateComponent(Args... args)
	{
		return ComponentManager::GetInstance().CreateComponent<ComponentT>(m_id, args...);
	}

	template <typename ComponentT>
	bool Entity::HaveComponent()
	{
		return ComponentManager::GetInstance().HaveComponent<ComponentT>(m_id);
	}

	template <typename ComponentT>
	void Entity::RemoveComponent()
	{
		ComponentManager::GetInstance().RemoveComponent<ComponentT>(m_id);
	}
}
