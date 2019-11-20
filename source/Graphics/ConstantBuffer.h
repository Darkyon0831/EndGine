#pragma once
#include <d3d11.h>

namespace EG
{
	class ConstantBuffer
	{
	public:
		ConstantBuffer();
		~ConstantBuffer() = default;

		void Update(void* var, size_t varSize);
			
		ID3D11Buffer* GetBuffer() const { return m_pBuffer; }
		
	private:
		ID3D11Buffer* m_pBuffer;
	};
}
