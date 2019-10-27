#pragma once

#include  <malloc.h>
#include  <cassert>
#include  <cstring>

namespace EG
{
	class LinearAllocator
	{
	public:
		void AllocBlock(size_t blockSize);
		void* Alloc(size_t size);
		void* Realloc(size_t sizeToAdd);
		void Free();

		void* GetFirst() const { return m_pStart; }
		size_t GetOffset() const { return m_offset; }
		size_t GetBlockSize() const { return m_blockSize; }
		
	private:
		void* m_pStart = nullptr;
		size_t m_offset = 0;
		size_t m_blockSize = 0;
	};
}
