#pragma once

#include "ECS/Entity.h"
#include "ECS/ComponentManager.h"

#include "Components/CameraComponent.h"

class ThirdCameraEntity : public EG::Entity
{
public:
	ThirdCameraEntity();

private:
	EG::CameraComponent* m_pCameraComponent;
};