#include "TestCube.h"

TestCube::TestCube()
{
	m_pRotationCube = CreateComponent<RotationCube>();
}

TestCube::~TestCube()
{
	RemoveComponent<RotationCube>();
}
