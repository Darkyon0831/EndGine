#pragma once

#include <d3d11.h>

namespace EG
{
	class ConstantBuffer
	{
	public:

		ConstantBuffer(size_t size);
		~ConstantBuffer();

		void Update(void* pMem) const;

		ID3D11Buffer* GetBuffer() const { return m_pBuffer; }
		
	private:	
		ID3D11Buffer* m_pBuffer;
		size_t m_size;
	};
}