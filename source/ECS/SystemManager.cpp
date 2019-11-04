#include "SystemManager.h"

EG::SystemManager::SystemManager()
	: m_currrentSystemIndex(0)
	, m_systemsPerPool(10)
{
}

EG::SystemManager::~SystemManager()
{
	for (auto it = m_poolAllocators.begin(); it != m_poolAllocators.end(); it++)
	{
		delete it->second;
	}

	m_poolAllocators.clear();
}

void EG::SystemManager::InitializeSystems()
{
	for (auto it = m_systems.begin(); it != m_systems.end(); it++)
	{
		ISystem* system = static_cast<ISystem*>(it->second);

		system->PreStart();
		system->Start();
		system->PostStart();
	}
}

void EG::SystemManager::UpdateSystems()
{
	for (auto it = m_systems.begin(); it != m_systems.end(); it++)
	{
		ISystem* system = static_cast<ISystem*>(it->second);

		system->PreUpdate();
		system->Update();
		system->PostStart();
		system->Render();
	}
}

int EG::SystemManager::CreateID()
{
	return m_currrentSystemIndex++;
}
