#pragma once

#include "RenderComponent.h"
#include "Model.h"

namespace EG
{
	class QuadComponent : public Component<QuadComponent>
	{
	public:
		QuadComponent();
		
	private:
		RenderComponent* m_pRenderComponent;
		Model* m_pModel;
	};
}
