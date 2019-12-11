#include "QuadComponent.h"

#include "ECS/ComponentManager.h"

#include "Entities/GameObject.h"

EG::QuadComponent::QuadComponent()
{
	m_pRenderComponent = GetGameObject()->CreateComponent<RenderComponent>();
	m_pModel = GetGameObject()->CreateComponent<Model>();

	EG::Mesh::Vertex* vertex = new EG::Mesh::Vertex[4];

	vertex[0].position.Set(-0.5f, 0.5f, 0.0f);
	vertex[0].color = EG::Color(1.0f, 1.0f, 1.0f);
	vertex[0].uv = EG::Vector2D(0.0f, 0.0f);
	vertex[1].position.Set(0.5f, 0.5f, 0.0f);
	vertex[1].color = EG::Color(1.0f, 1.0f, 1.0f);
	vertex[1].uv = EG::Vector2D(1.0f, 0.0f);
	vertex[2].position.Set(0.5f, -0.5f, 0.0f);
	vertex[2].color = EG::Color(1.0f, 1.0f, 1.0f);
	vertex[2].uv = EG::Vector2D(1.0f, 1.0f);
	vertex[3].position.Set(-0.5f, -0.5f, 0.0f);
	vertex[3].color = EG::Color(1.0f, 1.0f, 1.0f);
	vertex[3].uv = EG::Vector2D(0.0f, 1.0f);

	int* index = new int[6];

	index[0] = 0;
	index[1] = 1;
	index[2] = 3;

	index[3] = 1;
	index[4] = 2;
	index[5] = 3;

	EG::Texture* texture = new EG::Texture();
	texture->Load("textures/test.dds");

	Mesh* pMesh = new Mesh();
	pMesh->GetMaterial().SetColormap(texture);
	pMesh->SetVertexArray(vertex, 4);
	pMesh->SetIndexArray(index, 6);
	pMesh->GetMaterial().GetShader().Load("quad_simple_vertex.hlsl", "quad_simple_pixel.hlsl");

	m_pModel->AddMesh(pMesh);
}
