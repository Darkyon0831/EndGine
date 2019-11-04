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

