#include "Game.h"

#include "Entities/TestCube.h"
#include "Entities/TextTest.h"

#include "ECS/EntityManager.h"

void Game::InitializeEntities()
{
	// Create your entities here!

	EG::EntityManager::GetInstance().CreateEntity<TestCube>();
	EG::EntityManager::GetInstance().CreateEntity<TextTest>();
}
