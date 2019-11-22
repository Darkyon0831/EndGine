#pragma once

#include "ECS/Entity.h"
#include "ECS/ComponentManager.h"

#include "Components/CameraComponent.h"

class CameraEntity : public EG::Entity
{
public:
	CameraEntity();

private:
	EG::CameraComponent* m_pCameraComponent;
	EG::CameraComponent* m_pCameraComponent2;
};