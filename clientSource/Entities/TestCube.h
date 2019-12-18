#pragma once

#include "Entities/GameObject.h"
#include "Components/RotationCube.h"

class TestCube : public EG::GameObject
{
public:
	TestCube();
	~TestCube();

private:
	RotationCube* m_pRotationCube;
};