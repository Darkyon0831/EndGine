#pragma once

#include  <malloc.h>

namespace EG
{
	template <typename T>
	class PoolAllocator
	{
	public:
		struct Block
		{
			Block* next = nullptr;
			T* mem = nullptr;
		};

		T* Alloc();
		void Free(T* ptrToFree);

		T* AllocMultiple(size_t numberAlloc);
		Block* FindNext();
		
	private:
		Block m_first;
	};

	template <typename T>
	T* PoolAllocator<T>::Alloc()
	{
		if (m_first.mem != nullptr)
		{
			Block* next = FindNext();
			next = static_cast<Block*>(malloc(sizeof(Block)));
			next->mem = static_cast<T*>(malloc(sizeof(T)));
			return next->mem;
		}
		
		m_first.mem = static_cast<T*>(malloc(sizeof(T)));

		return m_first.mem;
	}

	template <typename T>
	void PoolAllocator<T>::Free(T* ptrToFree)
	{
		Block* next = m_first;
		Block* previous;
		bool found = false;
		
		while (next != nullptr)
		{
			if (next->mem == ptrToFree)
			{
				found = true;
				break;
			}

			previous = next;
			next = next->next;
		}

		free(next->mem);

		if (next->next != nullptr)
			previous->next = next->next;
	}

	template <typename T>
	T* PoolAllocator<T>::AllocMultiple(size_t numberAlloc)
	{
		T* first = Alloc();
		for (int i = 0; i < numberAlloc; i++)
		{
			Alloc();
		}

		return first;
	}

	template <typename T>
	typename PoolAllocator<T>::Block* PoolAllocator<T>::FindNext()
	{
		Block* next = m_first.next;
		while (next != nullptr)
			next = next->next;

		return next;
	}
}
