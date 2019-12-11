#pragma once

#include "ECS/Component.h"
#include "Components/QuadComponent.h"

class QuadTest : public EG::Component<QuadTest>
{
public:
	QuadTest();
	~QuadTest();

	void Update() override;
	
private:
	EG::QuadComponent* m_pQuad;
};