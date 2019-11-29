#pragma once

#include <unordered_map>
#include <typeindex>
#include <map>
#include <cassert>

#include "Globals/Singleton.h"
#include "Memory/PoolAllocator.h"
#include "Entity.h"

namespace EG
{
	class EntityManager : public Singleton<EntityManager>
	{
	public:
		EntityManager();
		~EntityManager();

		template <typename T, typename... Args>
		Entity* CreateEntity(Args... args);

		Entity* GetEntity(int entityID);
		const std::map<int, Entity*>& GetEntities() const;
		
	private:
		int CreateID();
		
		std::unordered_map<std::type_index, PoolAllocator*> m_poolAllocators;
		
		std::map<int, Entity*> m_entities;

		int m_currrentEntityIndex;
		size_t m_entitiesPerPool;
	};

	inline int EntityManager::CreateID()
	{
		return m_currrentEntityIndex++;
	}

	template <typename T, typename... Args>
	Entity* EntityManager::CreateEntity(Args... args)
	{
		PoolAllocator* poolAllocator = nullptr;
		auto it = m_poolAllocators.find(typeid(T));
	
		if (it != m_poolAllocators.end())
			poolAllocator = it->second;
		else
		{
			size_t newPoolSize = sizeof(T) * m_entitiesPerPool;
			poolAllocator = new PoolAllocator(newPoolSize, sizeof(T), alignof(T));
			m_poolAllocators.insert(std::pair<std::type_index, PoolAllocator*>(typeid(T), poolAllocator));
		}

		Entity* entity = static_cast<Entity*>(poolAllocator->Alloc());

		if (entity == nullptr)
			return entity;
		
		int id = CreateID();
		entity->m_id = id;
		
		T* ptr = reinterpret_cast<T*>(entity);
		ptr = new(ptr) T(args...);

		m_entities.insert(std::pair<int, Entity*>(entity->m_id, entity));
		
		return entity;
	}

	inline Entity* EntityManager::GetEntity(int entityID)
	{
		auto it = m_entities.find(entityID);

		if (it != m_entities.end())
			return static_cast<Entity*>(it->second);
		
		return nullptr;
	}
}
