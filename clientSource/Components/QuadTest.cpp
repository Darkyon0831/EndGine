#include "QuadTest.h"

#include "Entities/GameObject.h"
#include "Globals/Clock.h"

QuadTest::QuadTest()
{
	m_pQuad = GetGameObject()->CreateComponent<EG::QuadComponent>();

	GetGameObject()->GetComponent<EG::Model>()->GetMesh(0)->GetMaterial().SetColor(EG::Color(0.0f, 1.0f, 0.0f));

	GetGameObject()->GetTransform()->scale.x = 1920.0f;
	GetGameObject()->GetTransform()->scale.y = 1080.0f;
}

QuadTest::~QuadTest()
{
	GetGameObject()->RemoveComponent<EG::Mesh>();
}

void QuadTest::Update()
{
	const float deltaTime = EG::Clock::GetInstance().GetDeltaTime();

	//GetGameObject()->GetTransform()->rotation.y += deltaTime * 30;
}
