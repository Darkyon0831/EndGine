#pragma once

#include "ECS/Component.h"

#include "QuadComponent.h"
#include "CameraComponent.h"

namespace EG
{
	class Canvas : public Component<Canvas>
	{
	public:
		Canvas();
		~Canvas();
		
	private:
		QuadComponent* m_pQuad;
	};
}