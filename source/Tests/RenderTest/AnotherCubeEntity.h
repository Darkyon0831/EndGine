#pragma once
#include "Components/RenderComponent.h"

#include "ECS/Entity.h"

namespace EG
{
	class AnotherCubeEntity : public Entity
	{
	public:
		AnotherCubeEntity();

	private:
		EG::RenderComponent* m_pRenderComponent;
	};
}
