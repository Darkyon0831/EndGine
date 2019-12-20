#pragma once

#include "ECS/Component.h"
#include "Components/Model.h"
#include "Components/RenderComponent.h"
#include "Globals/String.h"

namespace EG
{
	class TextComponent : public Component<TextComponent>
	{
	public:

		struct CharacherIndexData
		{
			float left;
			float right;
			float up;
			float down;
			float width;
		};
		
		TextComponent();
		~TextComponent();

		void SetText(const String& rText) { m_text = rText; }
		String& GetText() { return m_text; }

		Model* GetTextModel() const { return m_pTextModel; }

		void PostStart() override;
		void PostUpdate() override;
		
	private:

		void LoadFontFile();
		void BuildMesh();

		std::vector<CharacherIndexData> m_characherIndexData;
		
		String m_fontFilePath;
		String m_text;

		Mesh* m_pMesh;
		Model* m_pTextModel;
		RenderComponent* m_pRenderComponent;
	};
}