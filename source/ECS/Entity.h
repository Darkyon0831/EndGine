#pragma once

#include "ComponentManager.h"
#include "Component.h"

namespace EG
{
	class Entity
	{
	public:
		friend class EntityManager;
		
		Entity() = default;
		~Entity() = default;

		template <typename ComponentT>
		Component<ComponentT>* GetComponent();

		template <typename ComponentT, typename... Args>
		Component<ComponentT>* CreateComponent(Args... args);

		template <typename ComponentT>
		bool HaveComponent();
		
	protected:
		int m_id;
	};

	template <typename ComponentT>
	Component<ComponentT>* Entity::GetComponent()
	{
		return ComponentManager::GetInstance().GetComponent<ComponentT>(m_id);
	}

	template <typename ComponentT, typename... Args>
	Component<ComponentT>* Entity::CreateComponent(Args... args)
	{
		return ComponentManager::GetInstance().CreateComponent<ComponentT>(m_id, args...);
	}

	template <typename ComponentT>
	bool Entity::HaveComponent()
	{
		return ComponentManager::GetInstance().HaveComponent<ComponentT>();
	}
}
