#pragma once

#include "ECS/Component.h"

class DeltaTimeComponent : public EG::Component<DeltaTimeComponent>
{
public:
	float deltaTime = 22222;
};