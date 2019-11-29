#pragma once

#include "ECS/Entity.h"
#include "ECS/ComponentManager.h"

#include "Components/CameraComponent.h"

class AnotherCameraEntity : public EG::Entity
{
public:
	AnotherCameraEntity();

private:
	EG::CameraComponent* m_pCameraComponent;
};