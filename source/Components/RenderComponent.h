#pragma once

#include "ECS/Component.h"

#include "Graphics/Model.h"
#include "Graphics/Shader.h"
#include "Graphics/Material.h"

namespace EG
{
	class RenderComponent : public Component<RenderComponent>
	{
	public:
		RenderComponent();
		~RenderComponent();

		void PostStart() override;
		void PostUpdate() override;

		void Update() override;

		void SetModel(Model& model) { m_model = model; };
		void SetShader(Shader& shader) { m_shader = shader; };

		Model& GetModel() { return m_model; }
		Shader& GetShader() { return m_shader; }

		void UpdateConstantBuffer(Shader::ShaderStage shaderStage, ID3D11Buffer* pConstantBuffer, ID3D11DeviceContext* pDeviceContext) const;

	private:
		Model m_model;
		Shader m_shader;
	};
}