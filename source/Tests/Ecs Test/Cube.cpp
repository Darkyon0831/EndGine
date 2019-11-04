#include "Cube.h"

#include "ECS/ComponentManager.h"
#include "Graphics/Mesh.h"

Cube::Cube()
{
	m_transform = static_cast<TransformComponent*>(EG::ComponentManager::GetInstance().CreateComponent<TransformComponent>(m_id));
	m_mesh = static_cast<MeshComponent*>(EG::ComponentManager::GetInstance().CreateComponent<MeshComponent>(m_id));

	MeshComponent::Vertex* vertex = new MeshComponent::Vertex[8];

	vertex[0].position.Set(-0.5f, 0.5f, -0.5f);
	vertex[0].color = EG::Color(0.0f, 0.0f, 1.0f);
	vertex[0].uv = EG::Vector2D(0.0f, 0.0f);
	vertex[1].position.Set(0.5f, 0.5f, -0.5f);
	vertex[1].color = EG::Color(0.0f, 0.0f, 1.0f);
	vertex[1].uv = EG::Vector2D(1.0f, 0.0f);
	vertex[2].position.Set(0.5f, -0.5f, -0.5f);
	vertex[2].color = EG::Color(0.0f, 0.0f, 1.0f);
	vertex[2].uv = EG::Vector2D(1.0f, 1.0f);
	vertex[3].position.Set(-0.5f, -0.5f, -0.5f);
	vertex[3].color = EG::Color(0.0f, 0.0f, 1.0f);
	vertex[3].uv = EG::Vector2D(0.0f, 1.0f);

	vertex[4].position.Set(0.5f, 0.5f, 0.5f);
	vertex[4].color = EG::Color(0.0f, 1.0f, .0f);
	vertex[4].uv = EG::Vector2D(0.0f, 0.0f);
	vertex[5].position.Set(0.5f, -0.5f, 0.5f);
	vertex[5].color = EG::Color(0.0f, 1.0f, 0.0f);
	vertex[5].uv = EG::Vector2D(0.0f, 1.0f);
	vertex[6].position.Set(-0.5f, 0.5f, 0.5f);
	vertex[6].color = EG::Color(0.0f, 1.0f, 0.0f);
	vertex[6].uv = EG::Vector2D(0.0f, 1.0f);
	vertex[7].position.Set(-0.5f, -0.5f, 0.5f);
	vertex[7].color = EG::Color(0.0f, 1.0f, 0.0f);
	vertex[7].uv = EG::Vector2D(1.0f, 1.0f);

	int* index = new int[36];

	// Z-planes
	index[0] = 0;
	index[1] = 1;
	index[2] = 3;

	index[3] = 1;
	index[4] = 2;
	index[5] = 3;

	index[6] = 4;
	index[7] = 6;
	index[8] = 7;

	index[9] = 7;
	index[10] = 5;
	index[11] = 4;

	// X-planes
	index[12] = 4;
	index[13] = 1;
	index[14] = 0;

	index[15] = 0;
	index[16] = 6;
	index[17] = 4;

	index[18] = 5;
	index[19] = 3;
	index[20] = 2;

	index[21] = 5;
	index[22] = 7;
	index[23] = 3;

	// Y-planes
	index[24] = 4;
	index[25] = 5;
	index[26] = 2;

	index[27] = 2;
	index[28] = 1;
	index[29] = 4;

	index[30] = 0;
	index[31] = 7;
	index[32] = 6;

	index[33] = 0;
	index[34] = 3;
	index[35] = 7;

	m_mesh->SetVertexArray(vertex, 8);
	m_mesh->SetIndexArray(index, 36);
}

Cube::~Cube()
{
	EG::ComponentManager::GetInstance().RemoveComponent<TransformComponent>(m_id);
	EG::ComponentManager::GetInstance().RemoveComponent<MeshComponent>(m_id);
}
