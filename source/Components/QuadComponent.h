#pragma once

#include "RenderComponent.h"
#include "Mesh.h"

namespace EG
{
	class QuadComponent : public Component<QuadComponent>
	{
	public:
		QuadComponent();
		
	private:
		RenderComponent* m_pRenderComponent;
		Mesh* m_pMesh;
	};
}
