#pragma once

#include "ECS/Component.h"
#include "Components/Mesh.h"
#include "Components/RenderComponent.h"

class RotationCube : public EG::Component<RotationCube>
{
public:
	RotationCube();
	~RotationCube();

	void Update() override;
	
private:
	EG::Mesh* m_pMesh;
	EG::RenderComponent* m_pRenderComponent;
};