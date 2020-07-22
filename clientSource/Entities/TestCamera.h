#pragma once

#include "Components/CameraComponent.h"
#include "Entities/GameObject.h"

class TestCamera : public EG::GameObject
{
public:
	TestCamera();
	~TestCamera();
	
private:
	EG::CameraComponent* m_pCameraComponent;
};