#pragma once

#include <unordered_map>
#include <typeindex>
#include <map>
#include <cassert>

#include "Globals/Singleton.h"
#include "Memory/PoolAllocator.h"
#include "Component.h"

namespace EG
{
	class ComponentManager : public Singleton<ComponentManager>
	{
	public:

		template <typename T>
		using iterator = T*;

		ComponentManager();
		~ComponentManager();

		template <typename T, typename... Args>
		Component<T>* CreateComponent(int entityID, Args... args);

		template <typename T>
		void RemoveComponent(int entityID);

		template <typename T>
		T* GetComponent(int entityID);

		template <typename T>
		bool HaveComponent(int entityID);

		template <typename T>
		iterator<T> Begin();

		template <typename T>
		iterator<T> End();

	private:
		int CreateID();

		std::unordered_map<std::type_index, PoolAllocator*> m_poolAllocators;

		std::map<int, std::unordered_map<std::type_index, void*>> m_entityComponentLookup;

		int m_currrentEntityIndex;
		size_t m_componentsPerPool;
	};

	inline int ComponentManager::CreateID()
	{
		return m_currrentEntityIndex++;
	}

	template <typename T, typename... Args>
	Component<T>* ComponentManager::CreateComponent(int entityID, Args... args)
	{
		PoolAllocator* poolAllocator = nullptr;
		auto it = m_poolAllocators.find(typeid(T));

		if (it != m_poolAllocators.end())
			poolAllocator = it->second;
		else
		{
			size_t newPoolSize = sizeof(T) * m_componentsPerPool;
			poolAllocator = new PoolAllocator(newPoolSize, sizeof(T), alignof(T));
			m_poolAllocators.insert(std::pair<std::type_index, PoolAllocator*>(typeid(T), poolAllocator));
		}

		Component<T>* component = static_cast<Component<T>*>(poolAllocator->Alloc());

		if (component == nullptr)
			return component;

		component->m_id = CreateID();

		T* ptr = static_cast<T*>(component);
		ptr = new(ptr) T(args...);

		auto entityComponentLookupIT = m_entityComponentLookup.find(entityID);
		std::unordered_map<std::type_index, void*>* componentMap = nullptr;
		
		if (entityComponentLookupIT == m_entityComponentLookup.end())
		{
			m_entityComponentLookup.insert(std::pair<int, std::unordered_map<std::type_index, void*>>(entityID, std::unordered_map<std::type_index, void*>()));
			entityComponentLookupIT = --m_entityComponentLookup.end();
			componentMap = &entityComponentLookupIT->second;
		}
		else
		{
			componentMap = &entityComponentLookupIT->second;
		}

		componentMap->insert(std::pair<std::type_index, void*>(typeid(T), component));

		return component;
	}

	template <typename T>
	void ComponentManager::RemoveComponent(int entityID)
	{
		auto entityComponentLookupIT = m_entityComponentLookup.find(entityID);
		
		if (entityComponentLookupIT != m_entityComponentLookup.end())
		{
			std::unordered_map<std::type_index, void*>* componentMap = &entityComponentLookupIT->second;
			auto componentIT = componentMap->find(typeid(T));

			if (componentIT != componentMap->end())
			{
				auto poolIT = m_poolAllocators.find(typeid(T));

				if (poolIT != m_poolAllocators.end())
				{
					PoolAllocator* poolAllocator = poolIT->second;
					poolAllocator->Free(&componentIT->second);
				}
			}
		}
	}

	template <typename T>
	T* ComponentManager::GetComponent(int entityID)
	{
		auto entityComponentLookupIT = m_entityComponentLookup.find(entityID);

		if (entityComponentLookupIT != m_entityComponentLookup.end())
		{
			std::unordered_map<std::type_index, void*>& rComponentMap = entityComponentLookupIT->second;

			auto componentIT = rComponentMap.find(typeid(T));

			if (componentIT != rComponentMap.end())
				return static_cast<T*>(componentIT->second);
		}

		return nullptr;
	}

	template <typename T>
	bool ComponentManager::HaveComponent(int entityID)
	{
		auto entityComponentLookupIT = m_entityComponentLookup.find(entityID);

		if (entityComponentLookupIT != m_entityComponentLookup.end())
		{
			std::unordered_map<std::type_index, void*>& rComponentMap = entityComponentLookupIT->second;

			auto componentIT = rComponentMap.find(typeid(T));

			if (componentIT != rComponentMap.end())
				return true;
		}
		
		return false;
	}

	template <typename T>
	ComponentManager::iterator<T> ComponentManager::Begin()
	{
		auto poolIT = m_poolAllocators.find(typeid(T));

		assert(poolIT != m_poolAllocators.end() && "Not valid entity type!");

		iterator<T> it = static_cast<iterator<T>>(poolIT->second->GetBegin());

		return it;
	}

	template <typename T>
	ComponentManager::iterator<T> ComponentManager::End()
	{
		auto poolIT = m_poolAllocators.find(typeid(T));

		assert(poolIT != m_poolAllocators.end() && "Not valid entity type!");

		iterator<T> it = static_cast<iterator<T>>(poolIT->second->GetBegin()) + (poolIT->second->GetUsedSize() / poolIT->second->GetChunkSize());

		return it;
	}
}