#include "QuadComponent.h"

#include "ECS/ComponentManager.h"

EG::QuadComponent::QuadComponent()
{
	m_pRenderComponent = reinterpret_cast<RenderComponent*>(EG::ComponentManager::GetInstance().CreateComponent<RenderComponent>(m_entityID));

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

	EG::Mesh* cubeMesh = new EG::Mesh();
	cubeMesh->SetIndexArray(index, 6);
	cubeMesh->SetVertexArray(vertex, 4);

	EG::Texture* texture = new EG::Texture();
	texture->Load("textures/white_default.dds");

	cubeMesh->GetMaterial().SetColormap(texture);

	m_pRenderComponent->GetModel().AddMesh(cubeMesh);

	m_pRenderComponent->GetShader().Load("quad_simple_vertex.hlsl", "quad_simple_pixel.hlsl");
}

void EG::QuadComponent::Update()
{
	m_pRenderComponent->SetShader(m_shader);
	m_pRenderComponent->GetModel().SetTransform(m_transform);
	m_pRenderComponent->GetModel().GetMesh(0)->SetMaterial(m_material);
}
