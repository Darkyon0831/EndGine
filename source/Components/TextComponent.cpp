#include "TextComponent.h"

#include "Entities/GameObject.h"

EG::TextComponent::TextComponent(EG::String fontFilePath)
	: m_fontFilePath(fontFilePath)
	, m_fontSize(18)
{
	m_pModel = GetGameObject()->CreateComponent<EG::Model>();
	m_pRenderComponent = GetGameObject()->CreateComponent<EG::RenderComponent>();
}

EG::TextComponent::~TextComponent()
{
	GetGameObject()->RemoveComponent<EG::Model>();
	GetGameObject()->RemoveComponent<EG::RenderComponent>();

	FT_Done_Face(m_face);
	FT_Done_FreeType(m_library);
}

void EG::TextComponent::PreStart()
{
	SetupFreeType();
	LoadCharacherData();
}

void EG::TextComponent::PostUpdate()
{
	if (m_oldText.Compare(m_text) == false)
		LoadCharacherData();

	BuildMesh();

	m_oldText = m_text;
}

void EG::TextComponent::BuildMesh()
{
	if (m_oldText.Compare(m_text) == false)
	{
		EG::Vector3D position = EG::Vector3D(0.0f, 0.0f, 0.0f);
		m_pModel->ClearMeshes();

		for (int i = 0; i < m_text.GetSize() - 1; i++)
		{
			SCharacher& characher = m_charachers.at(i);

			EG::Mesh::Vertex* vertex = new EG::Mesh::Vertex[4];

			vertex[0].position = EG::Vector3D(position.x + characher.bearing.x, position.y + characher.size.y - (characher.size.y - characher.bearing.y), 0.0f);
			vertex[1].position = EG::Vector3D(position.x + characher.bearing.x + characher.size.x, position.y + characher.size.y - (characher.size.y - characher.bearing.y), 0.0f);
			vertex[2].position = EG::Vector3D(position.x + characher.bearing.x, position.y - (characher.size.y - characher.bearing.y), 0.0f);
			vertex[3].position = EG::Vector3D(position.x + characher.bearing.x + characher.size.x, position.y - (characher.size.y - characher.bearing.y), 0.0f);

			vertex[0].color = EG::Color(1.0f, 1.0f, 1.0f);
			vertex[1].color = EG::Color(1.0f, 1.0f, 1.0f);
			vertex[2].color = EG::Color(1.0f, 1.0f, 1.0f);
			vertex[3].color = EG::Color(1.0f, 1.0f, 1.0f);

			vertex[0].uv = Vector2D(0.0f, 0.0f); 
			vertex[1].uv = Vector2D(1.0f, 0.0f); 
			vertex[2].uv = Vector2D(0.0f, 1.0f); 
			vertex[3].uv = Vector2D(1.0f, 1.0f); 

			int* index = new int[6];

			index[0] = 0;
			index[1] = 1;
			index[2] = 2;
			index[3] = 1;
			index[4] = 3;
			index[5] = 2;

			Mesh* pMesh = new Mesh();
			pMesh->GetMaterial().SetColormap(characher.pTexture);
			pMesh->SetVertexArray(vertex, 4);
			pMesh->SetIndexArray(index, 6);

			pMesh->GetMaterial().SetColor(m_color);
			pMesh->GetMaterial().GetShader().Load("font_simple_vertex.hlsl", "font_simple_pixel.hlsl");

			m_pModel->AddMesh(pMesh);

			position.x += characher.advance;
		}
	}
}

void EG::TextComponent::LoadCharacherData()
{
	m_charachers.clear();

	for (int i = 0; i < m_text.GetSize() - 1; i++)
	{
		SCharacher characher;
		characher.characher = m_text.GetString()[i];
		
		FT_Load_Char(m_face, m_text[i], FT_LOAD_RENDER);

		characher.size.x = m_face->glyph->bitmap.width;
		characher.size.y = m_face->glyph->bitmap.rows;
		characher.bearing.x = m_face->glyph->bitmap_left;
		characher.bearing.y = m_face->glyph->bitmap_top;
		characher.advance = m_face->glyph->advance.x >> 6;

		characher.pTexture = new Texture();

		if (m_text[i] != ' ')
		{
			characher.pTexture->LoadFromMemory(
			characher.size.x, 
			characher.size.y, 
			(char*)m_face->glyph->bitmap.buffer,
			m_face->glyph->bitmap.pitch);
		}

		m_charachers.push_back(characher);
	}
}

void EG::TextComponent::SetupFreeType()
{
	if (FT_Init_FreeType(&m_library))
	{
		// TODO: Add error handling here
	}

	if (FT_New_Face(m_library, m_fontFilePath.GetString(), 0, &m_face))
	{
		// TODO: Add error handling here
	}

	FT_Set_Pixel_Sizes(m_face, 0, m_fontSize);
}

