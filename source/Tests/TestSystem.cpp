#include "TestSystem.h"

#include "ECS/EntityManager.h"
#include "Tests/TestEntity.h"
#include "DeltaTimeComponent.h"

void EG::TestSystem::Start()
{
	const auto entities = EntityManager::GetInstance().GetEntities();

	for (auto it = entities.begin(); it != entities.end(); it++)
	{
		DeltaTimeComponent* component = static_cast<DeltaTimeComponent*>(it->second->GetComponent<DeltaTimeComponent>());
		
		if (component != nullptr)
			component->deltaTime = 0;
	}
}

void EG::TestSystem::Update()
{

}
