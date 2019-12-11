#pragma once

#include "Device.h"
#include "SwapChain.h"

#include "Globals/Vector3D.h"
#include "Globals/Color.h"
#include "Shader.h"
#include "Globals/Transform.h"
#include "Globals/Camera.h"
#include "Mesh.h"

#include <d3d11.h>
#include <vector>
#include "Material.h"


namespace EG
{
	class Model
	{
	public:
		Model();
		~Model();

		Transform& GetTransform() { return m_transform; }
		void SetTransform(const Transform& transform) { m_transform = transform; }

		void AddMesh(Mesh* pMesh) { m_meshes.push_back(pMesh); }

		size_t GetNumMeshes() const { return m_meshes.size(); }

		Mesh* GetMesh(const int index) const { return m_meshes.at(index); }
		
	private:
		std::vector<Mesh*> m_meshes;
		Transform m_transform;
	};
}
