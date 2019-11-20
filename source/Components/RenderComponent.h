#pragma once

#include "ECS/Component.h"

#include "Graphics/Mesh.h"
#include "Graphics/Shader.h"
#include "Graphics/Material.h"

namespace EG
{
	class RenderComponent : public Component<RenderComponent>
	{
	public:
		void PostStart() override;

	private:
		Mesh* m_pMesh;
		Shader* m_pShader;
		Material m_material;
	};
}