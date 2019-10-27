#pragma once

#include "Memory/LinearAllocator.h"

namespace EG
{
	class String
	{
	public:
		explicit String() = default;
		explicit String(const char* str);
		explicit String(int size);
		explicit String(const char& characher);
		~String();

		String(const String& other);

		char* GetString() const;
		void Copy(const String& other);
		size_t GetSize() const;

		void operator+=(const char& characher);
		void operator+=(const char* str);
		void operator=(const char* str);
		void operator=(const char& characher);

	private:
		LinearAllocator m_allocator;
		char* m_str = nullptr;
	};
}
