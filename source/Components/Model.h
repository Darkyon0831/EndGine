#pragma once

#include "ECS/Component.h"
#include "Graphics/Mesh.h"

#include <vector>

namespace EG
{
	class Model : public Component<Model>
	{
	public:

		Model();
		~Model();
		
		void AddMesh(Mesh* pMesh) { m_meshAssets.push_back(pMesh); }
		Mesh* GetMesh(const int index) { return m_meshAssets.at(index); }
		int GetTotalMeshes() const { return m_meshAssets.size(); }

		void ClearMeshes();
		
	private:
		std::vector<Mesh*> m_meshAssets;
	};
}