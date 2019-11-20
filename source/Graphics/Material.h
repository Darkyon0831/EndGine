#pragma once

#include "Texture.h"
#include "Globals/Color.h"

namespace EG
{
	class Material
	{
	public:

		Material() : m_pColormap(nullptr) {}
		
		void SetColor(const Color& color) { m_color = color; }
		Color& GetColor() { return m_color; }

		void SetColormap(Texture* pColorMap) { m_pColormap = pColorMap; }
		Texture* GetColormap() const { return m_pColormap; }
		
	private:
		Texture* m_pColormap;
		Color m_color;
	};
}