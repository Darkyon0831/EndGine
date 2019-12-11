#pragma once

#include "ECS/Component.h"

#include "Components/Model.h"
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

		void UpdateConstantBuffer(Shader& rShader, Shader::ShaderStage shaderStage, ID3D11Buffer* pConstantBuffer, ID3D11DeviceContext* pDeviceContext) const;
	};
}