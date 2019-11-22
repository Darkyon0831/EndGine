#pragma once

#include "ECS/Entity.h"
#include "ECS/ComponentManager.h"

#include "Components/RenderComponent.h"

class CubeEntity : public EG::Entity
{
public:
	CubeEntity();
	
private:
	EG::RenderComponent* m_pRenderComponent;
};