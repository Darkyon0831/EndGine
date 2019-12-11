#pragma once

#include "ECS/Component.h"
#include "Components/Model.h"
#include "Components/RenderComponent.h"

class RotationCube : public EG::Component<RotationCube>
{
public:
	RotationCube();
	~RotationCube();

	void Update() override;
	
private:
	EG::Model* m_pModel;
	EG::RenderComponent* m_pRenderComponent;
};