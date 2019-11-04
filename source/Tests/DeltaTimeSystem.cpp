#include "DeltaTimeSystem.h"
#include "ECS/EntityManager.h"
#include "DeltaTimeComponent.h"

void DeltaTimeSystem::PreStart()
{
	m_isFirst = true;
	const auto entities = EG::EntityManager::GetInstance().GetEntities();

	for (auto it = entities.begin(); it != entities.end(); it++)
	{
		DeltaTimeComponent* component = static_cast<DeltaTimeComponent*>(it->second->GetComponent<DeltaTimeComponent>());

		if (component != nullptr)
			component->deltaTime = 0;
	}
}

void DeltaTimeSystem::PreUpdate()
{
	if (m_isFirst)
	{
		m_oldTimepoint = std::chrono::high_resolution_clock::now();
		m_isFirst = false;
	}
	else
	{
		std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> timeSpan = std::chrono::duration_cast<std::chrono::duration<double>>(now - m_oldTimepoint);

		m_deltaTime = timeSpan.count();

		m_oldTimepoint = now;
	}

	const auto entities = EG::EntityManager::GetInstance().GetEntities();

	for (auto it = entities.begin(); it != entities.end(); it++)
	{
		DeltaTimeComponent* component = static_cast<DeltaTimeComponent*>(it->second->GetComponent<DeltaTimeComponent>());

		if (component != nullptr)
			component->deltaTime = m_deltaTime;
	}
}
