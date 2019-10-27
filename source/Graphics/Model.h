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

namespace EG
{
	class Camera;

	class Model
	{
	public:
		struct ConstantBufferVS
		{
			Matrix world;
			Matrix view;
			Matrix projection;
		};

		Model();
		~Model();

		void Update();

		// TODO: Use an camera manager instead, Do not take it in from an parameter to have a good user experience
		void Render(Camera& rCurrentCamera);

		Transform& GetTransform() { return m_transform; }

		void AddMesh(Mesh* pMesh) { m_meshes.push_back(pMesh); }
		
	private:
		std::vector<Mesh*> m_meshes;
		
		Shader simpleColorShader;

		Transform m_transform;
	};
}