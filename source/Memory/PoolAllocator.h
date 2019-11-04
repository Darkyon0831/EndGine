#pragma once

#include  <malloc.h>

namespace EG
{
	class PoolAllocator
	{		
	public:

		struct Node
		{
			Node* next = nullptr;
		};
		
		PoolAllocator(size_t totalSize, size_t chunkSize, size_t alignment);
		~PoolAllocator();

		void* Alloc();
		void Free(void** memoryToBeFreed);

		void* GetBegin() const { return m_block; }
		size_t GetSize() const { return m_blockSize; }
		size_t GetChunkSize() const { return m_chunkSize; }
		size_t GetUsedSize() const { return m_usedSize; }

	private:
		void* m_block;
		void* m_blockWithOffset;
		size_t m_blockSize;
		size_t m_chunkSize;
		size_t m_usedSize;

		Node* m_linkedList;
	};
}
