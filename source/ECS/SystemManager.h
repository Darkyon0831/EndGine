#pragma once

#include <unordered_map>
#include <typeindex>
#include <map>
#include <cassert>

#include "Globals/Singleton.h"
#include "Memory/PoolAllocator.h"
#include "System.h"

namespace EG
{
	class SystemManager : public Singleton<SystemManager>
	{
	public:

		template <typename T>
		using SystemIterator = T*;

		SystemManager();
		~SystemManager();

		void InitializeSystems();
		void UpdateSystems();

		template <typename T, typename... Args>
		System<T>* CreateSystem(Args... args);

		template <typename T>
		System<T>* GetSystem(int entityID);

		template <typename T>
		SystemIterator<T> Begin();

		template <typename T>
		SystemIterator<T> End();

	private:
		int CreateID();

		std::unordered_map<std::type_index, PoolAllocator*> m_poolAllocators;

		std::map<int, void*> m_systems;

		int m_currrentSystemIndex;
		size_t m_systemsPerPool;
	};

	template <typename T, typename... Args>
	System<T>* SystemManager::CreateSystem(Args... args)
	{
		PoolAllocator* poolAllocator = nullptr;
		auto it = m_poolAllocators.find(typeid(T));

		if (it != m_poolAllocators.end())
			poolAllocator = it->second;
		else
		{
			size_t newPoolSize = sizeof(T) * m_systemsPerPool;
			poolAllocator = new PoolAllocator(newPoolSize, sizeof(T), alignof(T));
			m_poolAllocators.insert(std::pair<std::type_index, PoolAllocator*>(typeid(T), poolAllocator));
		}

		System<T>* system = static_cast<System<T>*>(poolAllocator->Alloc());

		if (system == nullptr)
			return system;

		T* ptr = static_cast<T*>(system);
		ptr = new(ptr) T(args...);

		system->m_id = CreateID();

		m_systems.insert(std::pair<int, void*>(system->m_id, system));

		return ptr;
	}

	template <typename T>
	System<T>* SystemManager::GetSystem(int entityID)
	{
		auto it = m_systems.find(entityID);

		if (it != m_systems.end())
			return it->second;

		return nullptr;
	}

	template <typename T>
	SystemManager::SystemIterator<T> SystemManager::Begin()
	{
		auto poolIT = m_poolAllocators.find(typeid(T));

		assert(poolIT != m_poolAllocators.end() && "Not valid entity type!");

		SystemIterator<T> it = static_cast<SystemIterator<T>>(poolIT->second->GetBegin());

		return it;
	}

	template <typename T>
	SystemManager::SystemIterator<T> SystemManager::End()
	{
		auto poolIT = m_poolAllocators.find(typeid(T));

		assert(poolIT != m_poolAllocators.end() && "Not valid entity type!");

		SystemIterator<T> it = static_cast<SystemIterator<T>>(poolIT->second->GetBegin()) + (poolIT->second->GetUsedSize() / poolIT->second->GetChunkSize());

		return it;
	}
}