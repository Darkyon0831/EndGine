#pragma once

#include "Globals/Color.h"
#include "Globals/Vector3D.h"
#include "Globals/Vector2D.h"
#include "Device.h"

#include <d3d11.h>
#include "Material.h"

namespace EG
{
	class Mesh
	{
	public:
		Mesh();
		~Mesh();
		
		struct Vertex
		{
			Vector3D position;
			Color color;
			Vector2D uv;
		};

		void SetVertexArray(Vertex* vertexArray, size_t size);
		void SetIndexArray(int* indexArray, size_t size);
		Vertex* GetVertexArray() const { return m_vertexArray; }
		int* GetIndexArray() const { return m_indexArray; }

		ID3D11Buffer* GetVertexBuffer() const { return m_pVertexBuffer; }
		ID3D11Buffer* GetIndexBuffer() const { return m_pIndexBuffer; }

		size_t GetVertexCount() const { return m_vertexCount; }
		size_t GetIndexCount() const { return m_indexCount; }

		void SetMaterial(Material& rMaterial) { m_material = rMaterial; }
		Material& GetMaterial() { return m_material; }
		
	private:
		Vertex* m_vertexArray;
		int* m_indexArray;

		ID3D11Buffer* m_pVertexBuffer;
		ID3D11Buffer* m_pIndexBuffer;

		size_t m_vertexCount;
		size_t m_indexCount;

		Material m_material;
	};
}
