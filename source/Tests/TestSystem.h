#pragma once

#include "ECS/System.h"

namespace EG
{
	class TestSystem : public System<TestSystem>
	{
	public:
		void Start() override;
		void Update() override;
		
	};

}
