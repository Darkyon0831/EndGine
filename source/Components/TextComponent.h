#pragma once

#include "ECS/Component.h"
#include "Components/Model.h"
#include "Components/RenderComponent.h"
#include "Globals/String.h"

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H

namespace EG
{
	class TextComponent : public Component<TextComponent>
	{
	public:
		
		struct SCharacher
		{
			char characher;
			EG::Texture* pTexture;
			EG::Vector2D bearing;
			EG::Vector2D size;
			float advance;
		};

		TextComponent(EG::String fontFilePath);
		~TextComponent();

		void PreStart() override;

		void PostUpdate() override;

		void SetText(const EG::String& rText) { m_text = rText; }
		const EG::String& GetText() { return m_text; }

		void SetFontSize(const int& rFontSize) { m_fontSize = rFontSize; }
		const int& GetFontSize() { return m_fontSize; }

		void SetColor(const EG::Color& rColor) { m_color = rColor; }
		const EG::Color& GetColor() { return m_color; }

		void BuildMesh();
		void LoadCharacherData();

		void SetupFreeType();
		
	private:

		EG::Color m_color;
		EG::String m_oldText;
		EG::String m_text;
		EG::String m_fontFilePath;
		int m_fontSize;

		EG::Model* m_pModel;
		EG::RenderComponent* m_pRenderComponent;

		std::vector<SCharacher> m_charachers;

		FT_Library m_library;
		FT_Face m_face;
	};
}