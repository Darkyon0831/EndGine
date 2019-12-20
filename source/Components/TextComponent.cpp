#include "TextComponent.h"

#include "Entities/GameObject.h"

#include <fstream>
#include "Globals/File/FileSystem.h"

EG::TextComponent::TextComponent()
	: m_text("")
{
	m_pTextModel = GetGameObject()->CreateComponent<Model>();
	m_pRenderComponent = GetGameObject()->CreateComponent<RenderComponent>();

	m_pMesh = new Mesh();

	Texture* pTexture = new Texture();
	pTexture->Load("font/font.dds");

	m_pMesh->GetMaterial().SetColormap(pTexture);
	m_pMesh->GetMaterial().GetShader().Load("mesh_simple_vertex.hlsl", "mesh_simple_pixel.hlsl");

	m_pTextModel->AddMesh(m_pMesh);
}

EG::TextComponent::~TextComponent()
{
	GetGameObject()->RemoveComponent<Model>();
	GetGameObject()->RemoveComponent<RenderComponent>();
}

void EG::TextComponent::ReadPart(float& fValue, std::ifstream& rStream) const
{
	char characher;
	String str;
	
	rStream >> characher;
	while (characher != ';' && characher != '\n')
	{
		str += characher;
		rStream >> characher;		
	}	

	fValue = std::stof(str.GetString());
}

void EG::TextComponent::PostStart()
{
	LoadFontFile();
	BuildMesh();
}

void EG::TextComponent::PostUpdate()
{
	BuildMesh();
}

void EG::TextComponent::LoadFontFile()
{
	const String filePath = FileSystem::GetInstance().GetDataLocationForPath("font/testFont.data");
	
	std::ifstream fileIn(filePath.GetString());
	char temp;
	CharacherIndexData characherIndexdata;

	int i = 0;
	while ((temp = fileIn.peek()))
	{
		ReadPart(characherIndexdata.left, fileIn);
		ReadPart(characherIndexdata.right, fileIn);
		ReadPart(characherIndexdata.up, fileIn);
		ReadPart(characherIndexdata.down, fileIn);
		ReadPart(characherIndexdata.width, fileIn);
		ReadPart(characherIndexdata.height, fileIn);

		m_characherIndexData.push_back(characherIndexdata);

		if (i == 93)
			int dsadsa = 0;

		i++;
	}

	int dd = 0;
}

void EG::TextComponent::BuildMesh()
{
	const int padding = 2;
	const unsigned int vertexCount = (m_text.GetSize() - 1) * 4 * 2 - 4;
	const unsigned int indexCount = (m_text.GetSize() - 1) * 6 * 2 - 6;

	Mesh::Vertex* vertices = new Mesh::Vertex[vertexCount];
	int* indecies = new int[indexCount];

	float traverseX = 0;
	int currentVertexIndex = 0;
	int currentIndexIndex = 0;
	
	for (int i = 0; i < m_text.GetSize() - 1; i++)
	{
		/*const CharacherIndexData charData = m_characherIndexData.at(m_text[i] - 32);

		vertices[currentVertexIndex].position = Vector3D(traverseX, charData.size.y / 2.0f, 0.0f);
		vertices[currentVertexIndex].uv = Vector2D(charData.left, 0.0f);
		currentVertexIndex++;
		
		vertices[currentVertexIndex].position = Vector3D(traverseX + charData.size.x, charData.size.y / 2.0f, 0.0f);
		vertices[currentVertexIndex].uv = Vector2D(charData.right, 0.0f);
		currentVertexIndex++;
		
		vertices[currentVertexIndex].position = Vector3D(traverseX + charData.size.x, -charData.size.y / 2.0f, 0.0f);
		vertices[currentVertexIndex].uv = Vector2D(charData.right, 1.0f);
		currentVertexIndex++;
		
		vertices[currentVertexIndex].position = Vector3D(traverseX, -charData.size.y / 2.0f, 0.0f);
		vertices[currentVertexIndex].uv = Vector2D(charData.left, 1.0f);
		currentVertexIndex++;
		
		indecies[currentIndexIndex++] = currentVertexIndex - 4;
		indecies[currentIndexIndex++] = currentVertexIndex + 1 - 4;
		indecies[currentIndexIndex++] = currentVertexIndex + 3 - 4;
		indecies[currentIndexIndex++] = currentVertexIndex + 1 - 4;
		indecies[currentIndexIndex++] = currentVertexIndex + 2 - 4;
		indecies[currentIndexIndex++] = currentVertexIndex + 3 - 4;
*/
		//traverseX += charData.size.x;
		//
		//// Add padding mesh, only if it is not the last char

		//if (i + 1 != m_text.GetSize() - 1)
		//{
		//	vertices[currentVertexIndex].position = Vector3D(traverseX, charData.size.y / 2.0f, 0.0f);
		//	vertices[currentVertexIndex].uv = Vector2D(0.7f, 0.8f);
		//	currentVertexIndex++;

		//	vertices[currentVertexIndex].position = Vector3D(traverseX + padding, charData.size.y / 2.0f, 0.0f);
		//	vertices[currentVertexIndex].uv = Vector2D(0.7f, 0.8f);
		//	currentVertexIndex++;

		//	vertices[currentVertexIndex].position = Vector3D(traverseX + padding, -charData.size.y / 2.0f, 0.0f);
		//	vertices[currentVertexIndex].uv = Vector2D(0.7f, 0.8f);
		//	currentVertexIndex++;

		//	vertices[currentVertexIndex].position = Vector3D(traverseX, -charData.size.y / 2.0f, 0.0f);
		//	vertices[currentVertexIndex].uv = Vector2D(0.7f, 0.8f);
		//	currentVertexIndex++;

		//	indecies[currentIndexIndex++] = currentVertexIndex - 4;
		//	indecies[currentIndexIndex++] = currentVertexIndex + 1 - 4;
		//	indecies[currentIndexIndex++] = currentVertexIndex + 3 - 4;
		//	indecies[currentIndexIndex++] = currentVertexIndex + 1 - 4;
		//	indecies[currentIndexIndex++] = currentVertexIndex + 2 - 4;
		//	indecies[currentIndexIndex++] = currentVertexIndex + 3 - 4;

		//	traverseX += padding;
		//}
	}

	m_pMesh->SetVertexArray(vertices, vertexCount);
	m_pMesh->SetIndexArray(indecies, indexCount);
}
