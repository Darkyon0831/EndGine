#include "TextComponent.h"

#include "Entities/GameObject.h"

#include <fstream>
#include "Globals/File/FileSystem.h"

EG::TextComponent::TextComponent()
{
	m_pTextModel = GetGameObject()->CreateComponent<Model>();
	m_pRenderComponent = GetGameObject()->CreateComponent<RenderComponent>();
}

EG::TextComponent::~TextComponent()
{
	GetGameObject()->RemoveComponent<Model>();
	GetGameObject()->RemoveComponent<RenderComponent>();
}

void EG::TextComponent::PostStart()
{
	LoadFontFile();
	BuildMesh();
}

void EG::TextComponent::LoadFontFile()
{
	const String filePath = FileSystem::GetInstance().GetDataLocationForPath("font/testFont.data");
	
	std::ifstream fileIn(filePath.GetString());
	char temp;
	CharacherIndexData characherIndexdata;
	
	while (fileIn.get(temp))
	{
		fileIn >> characherIndexdata.left;
		fileIn >> characherIndexdata.right;
		fileIn >> characherIndexdata.size.x;
		fileIn >> characherIndexdata.size.y;

		m_characherIndexData.push_back(characherIndexdata);
	}

	int i = 0;
}

void EG::TextComponent::BuildMesh()
{
	const String testStr = "Adrian";
	
	Mesh* pMesh = new Mesh();

	Mesh::Vertex* vertices = new Mesh::Vertex[testStr.GetSize() - 1 * 6];
	int* indecies = new int[testStr.GetSize() - 1 * 6];

	float traverseX = 0;
	
	for (int i = 0; i < testStr.GetSize() - 1; i++)
	{
		const int vertexIndexStart = i * 6;
		const CharacherIndexData charData = m_characherIndexData.at(testStr[i] - 32);

		#pragma region First triangle strip
		vertices[vertexIndexStart].position = Vector3D(traverseX, charData.size.y / 2.0f, 0.0f);
		vertices[vertexIndexStart].uv = Vector2D(charData.left, 1.0f);
		indecies[i] = vertexIndexStart;

		vertices[vertexIndexStart + 1].position = Vector3D(traverseX + charData.size.x, charData.size.y / 2.0f, 0.0f);
		vertices[vertexIndexStart + 1].uv = Vector2D(charData.right, 1.0f);
		indecies[i] = vertexIndexStart + 1;
		
		vertices[vertexIndexStart + 2].position = Vector3D(traverseX, -charData.size.y / 2.0f, 0.0f);
		vertices[vertexIndexStart + 2].uv = Vector2D(charData.left, 0.0f);
		indecies[i] = vertexIndexStart + 2;
		#pragma endregion

		#pragma region Second triangle strip
		vertices[vertexIndexStart + 3].position = Vector3D(traverseX + charData.size.x, charData.size.y / 2.0f, 0.0f);
		vertices[vertexIndexStart + 3].uv = Vector2D(charData.right, 1.0f);
		indecies[i] = vertexIndexStart + 3;

		vertices[vertexIndexStart + 4].position = Vector3D(traverseX + charData.size.x, -charData.size.y / 2.0f, 0.0f);
		vertices[vertexIndexStart + 4].uv = Vector2D(charData.right, 0.0f);
		indecies[i] = vertexIndexStart + 4;

		vertices[vertexIndexStart + 5].position = Vector3D(traverseX, -charData.size.y / 2.0f, 0.0f);
		vertices[vertexIndexStart + 5].uv = Vector2D(charData.left, 0.0f);
		indecies[i] = vertexIndexStart + 5;
		#pragma endregion

		traverseX += charData.size.x;
	}

	pMesh->SetVertexArray(vertices, testStr.GetSize() - 1 * 6);
	pMesh->SetIndexArray(indecies, testStr.GetSize() - 1 * 6);

	Texture* pTexture = new Texture();
	pTexture->Load("font/testFont.dds");
	
	pMesh->GetMaterial().SetColormap(pTexture);

	m_pTextModel->AddMesh(pMesh);
}
