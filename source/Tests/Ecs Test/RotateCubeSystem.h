#pragma once

#include <ECS/System.h>

class RotateCubeSystem : public EG::System<RotateCubeSystem>
{
public:

	void Update() override;
};