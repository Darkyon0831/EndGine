#pragma once

#include "RenderComponent.h"

namespace EG
{
	class QuadComponent : public Component<QuadComponent>
	{
	public:
		QuadComponent();

		Material& GetMaterial() { return m_material; }
		void SetMaterial(const Material& material) { m_material = material; }

		Transform& GetTransform() { return m_transform; }
		void SetTransform(const Transform& transform) { m_transform = transform; }

		Shader& GetShader() { return m_shader; }
		void SetShader(const Shader& shader) { m_shader = shader; }

		void Update() override;
		
	private:
		Material m_material;
		Transform m_transform;
		Shader m_shader;
		
		RenderComponent* m_pRenderComponent;
	};
}
