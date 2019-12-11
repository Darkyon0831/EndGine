#pragma once

#include "Texture.h"
#include "Globals/Color.h"
#include "Core/Asset.h"
#include "Shader.h"

namespace EG
{
	class Material : public Asset
	{
	public:

		Material()
			: Asset(Asset::AssetType::AMaterial)
			, m_pColormap(nullptr)
		{}
		
		void SetColor(const Color& color) { m_color = color; }
		Color& GetColor() { return m_color; }

		void SetColormap(Texture* pColorMap) { m_pColormap = pColorMap; }
		Texture* GetColormap() const { return m_pColormap; }

		Shader& GetShader() { return m_shader; }
		
	private:
		Texture* m_pColormap;
		Color m_color;
		Shader m_shader;
	};
}