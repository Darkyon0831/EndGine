#include  "LinearAllocator.h"

void EG::LinearAllocator::AllocBlock(size_t blockSize)
{
	assert(blockSize > 0);
	
	m_pStart = malloc(blockSize);
	m_blockSize = blockSize;
}

void* EG::LinearAllocator::Alloc(size_t size)
{
	assert(size > 0);
	
	if (m_offset + size > m_blockSize)
		return nullptr;

	char* ptr = static_cast<char*>(m_pStart) + m_offset;
	m_offset += size;

	return ptr;
}

void* EG::LinearAllocator::Realloc(size_t sizeToAdd)
{
	void* newFirst = malloc(m_blockSize + sizeToAdd);
	memcpy(newFirst, m_pStart, m_blockSize);
	free(m_pStart);
	m_pStart = newFirst;

	m_blockSize += sizeToAdd;

	return m_pStart;
}

void EG::LinearAllocator::Free()
{
	free(m_pStart);
	m_blockSize = 0;
	m_offset = 0;
	m_pStart = nullptr;
}
