#pragma once

#include "Globals/Vector3D.h"

#include "ECS/Component.h"

class TransformComponent : public EG::Component<TransformComponent>
{
public:

	TransformComponent();
	
	EG::Vector3D position;
	EG::Vector3D rotation;
	EG::Vector3D scale;
};