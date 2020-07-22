#include "Game.h"

#include "Entities/TestCube.h"
#include "Entities/TextTest.h"
#include "Entities/TestQuad.h"

#include "ECS/EntityManager.h"
#include "Settings/WndSettings.h"

void Game::PreStart()
{
	// Edit engine settings here


}

void Game::InitializeEntities()
{
	// Create your entities here!

	EG::EntityManager::GetInstance().CreateEntity<TestCube>();
	EG::EntityManager::GetInstance().CreateEntity<TextTest>();
	/*TestQuad* quad = EG::EntityManager::GetInstance().CreateEntity<TestQuad>();

	quad->GetTransform()->scale.x = 500.0f;
	quad->GetTransform()->scale.y = 500.0f;
	quad->GetTransform()->position.x = -250;
	quad->GetTransform()->position.y = 250;
	quad->GetTransform()->rotation.z = 180.0f;*/
	//quad->GetTransform()->rotation.x = 75.0f;
	//quad->GetTransform()->rotation.y = 45.0f;


	int i = 0;
}
