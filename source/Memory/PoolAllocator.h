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
		
		PoolAllocator(size_t totalSize, size_t chunkSize);
		~PoolAllocator();

		void* Alloc();
		void Free(void** memoryToBeFreed);
		
	private:
		void* m_block;
		size_t m_blockSize;
		size_t m_chunkSize;
		size_t m_usedSize;

		Node* m_linkedList;
	};
}
