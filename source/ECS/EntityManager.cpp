#include "EntityManager.h"

EG::EntityManager::EntityManager()
	: m_currrentEntityIndex(0)
	, m_entitiesPerPool(35)
{
	
}

EG::EntityManager::~EntityManager()
{
	for (auto it = m_poolAllocators.begin(); it != m_poolAllocators.end(); it++)
	{
		delete it->second;
	}

	m_poolAllocators.clear();
}

const std::map<int, EG::Entity*>& EG::EntityManager::GetEntities() const
{
	return m_entities;
}
