#include "RotateCubeSystem.h"

#include "ECS/EntityManager.h"
#include "TransformComponent.h"
#include "Globals/Clock.h"

void RotateCubeSystem::Update()
{
	EG::Entity* cubeEntity = EG::EntityManager::GetInstance().GetEntity(0);
	float deltaTime = EG::Clock::GetInstance().GetDeltaTime();
	
	TransformComponent* transform = static_cast<TransformComponent*>(cubeEntity->GetComponent<TransformComponent>());

	transform->scale.x = sin(EG::Clock::GetInstance().GetLifeTime() * 2) * 4;
	transform->rotation.y += EG::Clock::GetInstance().GetDeltaTime() * 50;

	int debug = 0;
}
