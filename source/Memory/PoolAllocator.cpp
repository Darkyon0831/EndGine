#include "PoolAllocator.h"
#include <cassert>
#include <cstdlib>

EG::PoolAllocator::PoolAllocator(const size_t totalSize, const size_t chunkSize, const size_t alignment)
	: m_block(nullptr)
	, m_blockSize(totalSize)
	, m_chunkSize(chunkSize)
	, m_usedSize(0)
{
	assert(totalSize % chunkSize == 0 && "Total size must be a multible of chunk size");
	assert(chunkSize >= sizeof(void*) && "Chunk size is a minimum of 8");

	m_blockWithOffset = malloc(totalSize + alignment - 1);
	m_block = reinterpret_cast<void*>((reinterpret_cast<size_t>(m_blockWithOffset) + alignment - 1 & ~alignment));
	
	// Split the memory and fill the linked list

	m_linkedList = static_cast<Node*>(m_block);

	size_t currentSize = 0;

	char* blockChar = static_cast<char*>(m_block);
	Node* currentNode = m_linkedList;

	while (currentSize != m_blockSize - m_chunkSize)
	{
		currentNode->next = reinterpret_cast<Node*>(blockChar + (currentSize + m_chunkSize));
		currentSize += m_chunkSize;
		currentNode = currentNode->next;

		if (currentSize == m_blockSize - m_chunkSize)
			currentNode->next = nullptr;
	}

	int debug = 0;
}

EG::PoolAllocator::~PoolAllocator()
{
	if (m_block != nullptr)
		free(m_block);
}

void* EG::PoolAllocator::Alloc()
{
	if (m_usedSize == m_blockSize)
		return nullptr;
	
	Node* toReturn = m_linkedList;

	if (m_linkedList->next != nullptr)
		m_linkedList = m_linkedList->next;

	m_usedSize += m_chunkSize;

	return toReturn;
}

void EG::PoolAllocator::Free(void** memoryToBeFreed)
{
	Node* next = m_linkedList;

	m_linkedList = static_cast<Node*>(*memoryToBeFreed);

	m_linkedList->next = next;

	*memoryToBeFreed = nullptr;
}
