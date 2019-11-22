#include "ComponentManager.h"

EG::ComponentManager::ComponentManager()
	: m_currrentEntityIndex(0)
	, m_componentsPerPool(50)
{
	
}

EG::ComponentManager::~ComponentManager()
{
	for (auto it = m_poolAllocators.begin(); it != m_poolAllocators.end(); it++)
	{
		delete it->second;
	}

	m_poolAllocators.clear();
}

void EG::ComponentManager::StartComponents()
{
	for (auto entitytIT = m_entityComponentLookup.begin(); entitytIT != m_entityComponentLookup.end(); entitytIT++)
	{
		for (auto componentIT = entitytIT->second.begin(); componentIT != entitytIT->second.end(); componentIT++)
		{
			componentIT->second->PreStart();
		}
	}

	for (auto entitytIT = m_entityComponentLookup.begin(); entitytIT != m_entityComponentLookup.end(); entitytIT++)
	{
		for (auto componentIT = entitytIT->second.begin(); componentIT != entitytIT->second.end(); componentIT++)
		{
			componentIT->second->Start();
		}
	}

	for (auto entitytIT = m_entityComponentLookup.begin(); entitytIT != m_entityComponentLookup.end(); entitytIT++)
	{
		for (auto componentIT = entitytIT->second.begin(); componentIT != entitytIT->second.end(); componentIT++)
		{
			componentIT->second->PostStart();
		}
	}
}

void EG::ComponentManager::UpdateComponents()
{
	for (auto entitytIT = m_entityComponentLookup.begin(); entitytIT != m_entityComponentLookup.end(); entitytIT++)
	{
		for (auto componentIT = entitytIT->second.begin(); componentIT != entitytIT->second.end(); componentIT++)
		{
			componentIT->second->PreUpdate();
		}
	}

	for (auto entitytIT = m_entityComponentLookup.begin(); entitytIT != m_entityComponentLookup.end(); entitytIT++)
	{
		for (auto componentIT = entitytIT->second.begin(); componentIT != entitytIT->second.end(); componentIT++)
		{
			componentIT->second->Update();
		}
	}

	for (auto entitytIT = m_entityComponentLookup.begin(); entitytIT != m_entityComponentLookup.end(); entitytIT++)
	{
		for (auto componentIT = entitytIT->second.begin(); componentIT != entitytIT->second.end(); componentIT++)
		{
			componentIT->second->PostUpdate();
		}
	}
}

