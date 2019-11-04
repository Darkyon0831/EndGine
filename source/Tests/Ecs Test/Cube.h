#pragma once

#include "ECS/Entity.h"
#include "TransformComponent.h"
#include "MeshComponent.h"

class Cube : public EG::Entity
{
public:
	Cube();
	~Cube();
	
private:
	TransformComponent* m_transform;
	MeshComponent* m_mesh;
};